//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#ifndef __HPX_BROADCAST_BINARY_HPP__
#define __HPX_BROADCAST_BINARY_HPP__

#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unistd.h>

#include <hpx/include/async.hpp>
#include <hpx/lcos/barrier.hpp>
#include <hpx/lcos/distributed_object.hpp>

#include "collective_traits.hpp" 
#include "serialization.hpp"
#include "broadcast.hpp"

using hpx::lcos::distributed_object;

REGISTER_DISTRIBUTED_OBJECT_PART(std::tuple<std::int32_t, std::string>);

namespace hpx { namespace utils { namespace collectives {

template<typename BlockingPolicy, typename Serialization >
class broadcast<tree_binary, BlockingPolicy, Serialization> {

    using value_type_t = typename Serialization::value_type;
    using serializer_t = typename Serialization::serializer;
    using deserializer_t = typename Serialization::deserializer;

private:
    std::int64_t root, cas_count, rel_rank, left, right;
    distributed_object< std::tuple< std::int32_t , std::string > > args;

public:
    using communication_pattern = hpx::utils::collectives::tree_binary;
    using blocking_policy = BlockingPolicy;

    broadcast(const std::string agas_name, const std::int64_t root_=0) :
        root(root_),
        cas_count(0),
        rel_rank(0),
        left(0),
        right(0),
        args{agas_name, std::make_tuple(0, std::string{})} {

        const auto rank_n = hpx::final_all_localities().size();

        rel_rank = (hpx::get_locality_id() + root_) % rank_n;
        left = (2*rel_rank) + 1;
        right = (2*rel_rank) + 2;
        cas_count = ( left < rank_n ) + ( right < rank_n );
    }

    template<typename DataType>
    void operator()(DataType & data) {

        const std::int64_t rank_n = hpx::final_all_localities().size();
        const std::int64_t rank_me = rel_rank;
        const bool post_lleaf = left < rank_n;
        const bool post_rleaf = right < rank_n;

        // i.am.root.
        if(rank_me == 0) {

            value_type_t value_buffer{};
            serializer_t value_oa = Serialization::make_serializer(value_buffer);

            if(post_lleaf) {
                hpx::async(
                    left,
                    [](distributed_object< std::tuple<std::int32_t, std::string> > & args_, std::string data_) {
                        std::get<1>(*args_).resize(data_.size());
                        std::get<1>(*args_).insert(0, data_);
                        atomic_xchange( &std::get<0>(*args_), 0, 1 );
                    }, std::ref(args), Serialization::get_buffer(value_buffer)
                );
            }
            if(post_rleaf) {
                hpx::async(
                    right,
                    [](distributed_object< std::tuple<std::int32_t, std::string> > & args_, std::string data_) {
                        std::get<1>(*args_).resize(data_.size());
                        std::get<1>(*args_).insert(0, data_);
                        atomic_xchange( &std::get<0>(*args_), 0, 1 );
                    }, std::ref(args), Serialization::get_buffer(value_buffer)
                );
            }
        }
        else {

            while(!atomic_xchange( &std::get<0>(*args), 1, 0 )) {
            }

            if(post_lleaf) {
                hpx::async(
                    left,
                    [](distributed_object< std::tuple<std::int32_t, std::string> > & args_, std::string data_) {
                        std::get<1>(*args_).resize(data_.size());
                        std::get<1>(*args_).insert(0, data_);
                        atomic_xchange( &std::get<0>(*args_), 0, 1 );
                    }, std::ref(args), std::get<1>(*args)
                );
            }
            if(post_rleaf) {
                hpx::async(
                    right,
                    [](distributed_object< std::tuple<std::int32_t, std::string> > & args_, std::string data_) {
                        std::get<1>(*args_).resize(data_.size());
                        std::get<1>(*args_).insert(0, data_);
                        atomic_xchange( &std::get<0>(*args_), 0, 1 );
                    }, std::ref(args), std::get<1>(*args)
                );
            }

            value_type_t value_buffer{std::get<1>(*args)};
            deserializer_t value_ia = Serialization::make_serializer(value_buffer);

            std::int64_t recv_rank = 0;
            value_ia >> recv_rank >> data;
        }

        if constexpr(is_blocking<BlockingPolicy>()) {
            hpx::lcos::barrier b("wait_for_completion", hpx::final_all_localities().size(), hpx::get_locality_id());
            b.wait(); // make sure communications terminate properly
        }

    } // end operator()

};

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

#endif
