//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//   
#pragma once
#ifndef __HPX_COLLECTIVES_HPP__
#define __HPX_COLLECTIVES_HPP__

#include "collective_traits.hpp"
#include "serialization.hpp"
#include "broadcast.hpp"
#include "broadcast_binomial.hpp"
#include "broadcast_binary.hpp"
#include "scatter.hpp"
#include "scatter_binomial.hpp"
#include "scatter_binary.hpp"
#include "gather.hpp"
#include "gather_binary.hpp"
#include "gather_binomial.hpp"
#include "reduce.hpp"
#include "reduce_binary.hpp"
#include "reduce_binomial.hpp"

namespace hpx { namespace utils { namespace collectives {

template<typename Operation>
class scalar_collective {

private:
    const std::int64_t root;

public:
    scalar_collective(const std::int64_t root_=0) :
        root(root_) {
    }

    template<typename DataType>
    void operator()(DataType & data) {
        Operation op{root};
        op(data);
    }
};

template<typename Operation>
class iterable_collective {

private:
    const std::int64_t root;

public:
    iterable_collective(const std::int64_t root_=0) :
        root(root_) {
    }

    template<typename InputIter, typename OutputIter>
    void operator()(InputIter input_beg, InputIter input_end, OutputIter output_beg) {
        Operation op{root};
        op(input_beg, input_end, output_beg);
    }

    template<typename InputIterator, typename BinaryOp>
    void operator()(InputIterator input_beg, InputIterator input_end, typename std::iterator_traits<InputIterator>::value_type init, BinaryOp op, typename std::iterator_traits<InputIterator>::value_type & output) {
        Operation opr{};
        opr(input_beg, input_end, init, op, output);
    }

/*
    template<class ExecutionPolicy, typename InputIterator, typename BinaryOp>
    void operator()(ExecutionPolicy && policy, InputIterator input_beg, InputIterator input_end, typename std::iterator_traits<InputIterator>::value_type init, BinaryOp op, typename std::iterator_traits<InputIterator>::value_type & output) {
        Operation opr{};
        opr(input_beg, input_end, init, op, output);
    }
*/

};

// broadcast
//
using nonblocking_binomial_broadcast = hpx::utils::collectives::scalar_collective<hpx::utils::collectives::broadcast<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binomial_broadcast = hpx::utils::collectives::scalar_collective<hpx::utils::collectives::broadcast<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

using nonblocking_binary_broadcast = hpx::utils::collectives::scalar_collective<hpx::utils::collectives::broadcast<hpx::utils::collectives::tree_binary, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binary_broadcast = hpx::utils::collectives::scalar_collective<hpx::utils::collectives::broadcast<hpx::utils::collectives::tree_binary, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

// scatter
//
using nonblocking_binomial_scatter = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::scatter<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binomial_scatter = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::scatter<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

using nonblocking_binary_scatter = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::scatter<hpx::utils::collectives::tree_binary, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binary_scatter = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::scatter<hpx::utils::collectives::tree_binary, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

// gather
//
using nonblocking_binary_gather = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::gather<hpx::utils::collectives::tree_binary, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binary_gather = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::gather<hpx::utils::collectives::tree_binary, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

using nonblocking_binomial_gather = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::gather<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binomial_gather = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::gather<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

// reduce
//
using nonblocking_binary_reduce = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::reduce<hpx::utils::collectives::tree_binary, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binary_reduce = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::reduce<hpx::utils::collectives::tree_binary, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

using nonblocking_binomial_reduce = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::reduce<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::nonblocking, hpx::utils::collectives::serialization::backend>>;
using blocking_binomial_reduce = hpx::utils::collectives::iterable_collective<hpx::utils::collectives::reduce<hpx::utils::collectives::tree_binomial, hpx::utils::collectives::blocking, hpx::utils::collectives::serialization::backend>>;

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

#endif
