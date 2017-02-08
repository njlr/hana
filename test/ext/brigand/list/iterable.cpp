// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/ext/brigand/list.hpp>

#include <boost/hana/assert.hpp>
#include <boost/hana/drop_front_exactly.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <laws/iterable.hpp>

#include <brigand/sequences/list.hpp>
namespace hana = boost::hana;


struct t1; struct t2; struct t3; struct t4;

int main() {
    // front
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(brigand::list<t1>{}),
            hana::type_c<t1>
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(brigand::list<t1, t2>{}),
            hana::type_c<t1>
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(brigand::list<t1, t2, t3>{}),
            hana::type_c<t1>
        ));
    }

    // drop_front_exactly
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1>{}),
            brigand::list<>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1, t2>{}),
            brigand::list<t2>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1, t2, t3>{}),
            brigand::list<t2, t3>{}
        ));


        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1, t2, t3>{}, hana::size_c<2>),
            brigand::list<t3>{}
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1, t2, t3, t4>{}, hana::size_c<2>),
            brigand::list<t3, t4>{}
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(brigand::list<t1, t2, t3, t4>{}, hana::size_c<3>),
            brigand::list<t4>{}
        ));
    }

    // is_empty
    {
        BOOST_HANA_CONSTANT_CHECK(hana::is_empty(brigand::list<>{}));
        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(brigand::list<t1>{})));
        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(brigand::list<t1, t2>{})));
    }

    // laws
    auto lists = hana::make_tuple(
          brigand::list<>{}
        , brigand::list<t1>{}
        , brigand::list<t1, t2>{}
        , brigand::list<t1, t2, t3>{}
        , brigand::list<t1, t2, t3, t4>{}
    );
    hana::test::TestIterable<hana::ext::brigand::list_tag>{lists};
}
