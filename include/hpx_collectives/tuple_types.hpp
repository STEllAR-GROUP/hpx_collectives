#include <cstdint>
//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

namespace hpx { namespace utils { namespace collectives {

using int_string_tuple_type = std::tuple<std::int32_t, std::string>;

using int_vector_string_tuple_type =
    std::tuple<std::int32_t, std::vector<std::string>>;

using int_int_string_string_tuple_type = std::tuple<std::int32_t,
    std::int32_t, std::string, std::string>;

using int_int_vector_string_vector_string_tuple_type = std::tuple<std::int32_t,
    std::int32_t, std::vector<std::string>, std::vector<std::string>>;

} /* end namespace collectives */ } /* end namespace utils */ } /* end namespace hpx */

REGISTER_DISTRIBUTED_OBJECT_PART_DECLARATION(
    hpx::utils::collectives::int_string_tuple_type);
REGISTER_DISTRIBUTED_OBJECT_PART_DECLARATION(
    hpx::utils::collectives::int_vector_string_tuple_type);
REGISTER_DISTRIBUTED_OBJECT_PART_DECLARATION(
    hpx::utils::collectives::int_int_string_string_tuple_type);
REGISTER_DISTRIBUTED_OBJECT_PART_DECLARATION(
    hpx::utils::collectives::int_int_vector_string_vector_string_tuple_type);

