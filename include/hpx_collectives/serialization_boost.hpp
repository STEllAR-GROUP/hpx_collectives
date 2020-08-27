//  Copyright (c) 2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#ifndef __HPX_COLLECTIVES_SERIALIZER_BOOST__
#define __HPX_COLLECTIVES_SERIALIZER_BOOST__

#include <type_traits>
#include <sstream>

#ifdef BOOST
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
#endif

namespace hpx { namespace utils { namespace collectives { namespace serialization {

#ifdef BOOST

struct boost {
    using value_type = std::stringstream;
    using serializer = ::boost::archive::binary_oarchive;
    using deserializer = ::boost::archive::binary_iarchive;

    static std::string get_buffer(const value_type & vt) {
        return vt.str();
    }
};

#else

struct boost {};

#endif

template<typename Tag>
struct is_boost : public std::false_type {
};

template<>
struct is_boost< ::hpx::utils::collectives::serialization::boost> : public std::true_type {
};

} } } } // end namespaces

#endif
