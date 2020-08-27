//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#ifndef __HPX_SCATTER_HPP__
#define __HPX_SCATTER_HPP__

#include "collective_traits.hpp"
#include "hpx_collectives/tuple_types.hpp"

#include <cstdint>

namespace hpx { namespace utils { namespace collectives {

template< typename CommunicationPattern, typename BlockingPolicy, typename Serialization >
class scatter {

public:
    using communication_pattern = CommunicationPattern;
    using blocking_policy = BlockingPolicy;

    scatter(const std::int64_t root_=0);

    template<typename InputIterator, typename OutputIterator>
    void operator()(InputIterator input_beg, InputIterator input_end, OutputIterator out_beg);

};

using binary_scatter_tuple_type = int_vector_string_tuple_type;
using binomial_scatter_tuple_type = int_string_tuple_type;

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

#endif
