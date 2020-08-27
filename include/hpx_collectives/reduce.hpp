//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#ifndef __HPX_REDUCE_HPP__
#define __HPX_REDUCE_HPP__

#include "collective_traits.hpp"
#include "hpx_collectives/tuple_types.hpp"

#include <cstdint>

namespace hpx { namespace utils { namespace collectives {

template< typename CommunicationPattern, typename BlockingPolicy, typename Serialization >
class reduce {

public:
    using communication_pattern = CommunicationPattern;
    using blocking_policy = BlockingPolicy;

    reduce(const std::int64_t root_=0);

    template<typename InputIterator, typename BinaryOp>
    void operator()(InputIterator input_beg, InputIterator input_end, typename std::iterator_traits<InputIterator>::value_type init, BinaryOp op, typename std::iterator_traits<InputIterator>::value_type & output);

};

using binary_reduce_tuple_type = int_int_string_string_tuple_type;
using binomial_reduce_tuple_type = int_vector_string_tuple_type;

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

#endif
