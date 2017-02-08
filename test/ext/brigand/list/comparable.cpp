// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/ext/brigand/list.hpp>

#include <boost/hana/tuple.hpp>

#include <laws/comparable.hpp>

#include <brigand/sequences/list.hpp>
namespace hana = boost::hana;


struct t1; struct t2; struct t3; struct t4;

int main() {
    auto lists = hana::make_tuple(
          brigand::list<>{}
        , brigand::list<t1>{}
        , brigand::list<t1, t2>{}
        , brigand::list<t1, t2, t3>{}
        , brigand::list<t1, t2, t3, t4>{}
    );

    hana::test::TestComparable<hana::ext::brigand::list_tag>{lists};
}
