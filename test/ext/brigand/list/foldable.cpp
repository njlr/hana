// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/ext/brigand/list.hpp>

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/type.hpp>

#include <laws/base.hpp>
#include <laws/foldable.hpp>

#include <brigand/sequences/list.hpp>
namespace hana = boost::hana;


struct t1; struct t2; struct t3; struct t4;

int main() {
    // unpack
    {
        hana::test::_injection<0> f{};
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(brigand::list<>{}, f),
            f()
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(brigand::list<t1>{}, f),
            f(hana::type_c<t1>)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(brigand::list<t1, t2>{}, f),
            f(hana::type_c<t1>, hana::type_c<t2>)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(brigand::list<t1, t2, t3>{}, f),
            f(hana::type_c<t1>, hana::type_c<t2>, hana::type_c<t3>)
        ));
    }

    // laws
    auto lists = hana::make_tuple(
          brigand::list<>{}
        , brigand::list<t1>{}
        , brigand::list<t1, t2>{}
        , brigand::list<t1, t2, t3>{}
        , brigand::list<t1, t2, t3, t4>{}
    );

    hana::test::TestFoldable<hana::ext::brigand::list_tag>{lists};
}
