//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#ifndef __HPX_BROADCAST_HPP__
#define __HPX_BROADCAST_HPP__

#include <hpx/lcos/distributed_object.hpp>

#include "collective_traits.hpp"
#include "hpx_collectives/tuple_types.hpp"

#include <cstdint>

namespace hpx { namespace utils { namespace collectives {

template< typename CommunicationPattern, typename BlockingPolicy, typename Serialization >
class broadcast {

public:
    using communication_pattern = CommunicationPattern;
    using blocking_policy = BlockingPolicy;

    broadcast(const std::int64_t root=0);

    template<typename DataType>
    void operator()(DataType & data);

};

using broadcast_tuple_type = int_string_tuple_type;

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

#endif
