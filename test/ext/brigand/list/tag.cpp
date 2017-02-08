// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/ext/brigand/list.hpp>

#include <boost/hana/core/tag_of.hpp>

#include <brigand/sequences/list.hpp>

#include <type_traits>
namespace hana = boost::hana;


struct t1; struct t2; struct t3; struct t4;

static_assert(std::is_same<
    hana::tag_of_t<brigand::list<>>,
    hana::ext::brigand::list_tag
>{}, "");
static_assert(std::is_same<
    hana::tag_of_t<brigand::list<t1>>,
    hana::ext::brigand::list_tag
>{}, "");
static_assert(std::is_same<
    hana::tag_of_t<brigand::list<t1, t2>>,
    hana::ext::brigand::list_tag
>{}, "");
static_assert(std::is_same<
    hana::tag_of_t<brigand::list<t1, t2, t3>>,
    hana::ext::brigand::list_tag
>{}, "");
static_assert(std::is_same<
    hana::tag_of_t<brigand::list<t1, t2, t3, t4>>,
    hana::ext::brigand::list_tag
>{}, "");

int main() { }
