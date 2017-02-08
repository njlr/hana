/*!
@file
Adapts `brigand::list` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BRIGAND_LIST_HPP
#define BOOST_HANA_EXT_BRIGAND_LIST_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <brigand/brigand/sequences/at.hpp>
#include <brigand/brigand/sequences/list.hpp>
#include <brigand/brigand/sequences/size.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace brigand {
    //! @ingroup group-ext-brigand
    //! Adapter for Brigand lists.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! It is possible for Brigand lists to model a couple of concepts.
    //! However, because they are only able to hold types, they lack
    //! the generality required to model concepts like `Functor`,
    //! `Sequence` and other related concepts.
    //!
    //! 1. `Comparable`\n
    //! Two Brigand lists are equal if and only if they contain the same
    //! number of types, and if all those types are equal.
    //! @include example/ext/brigand/list/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding a Brigand list is equivalent to folding it as a `Sequence`.
    //! @include example/ext/brigand/list/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over a Brigand list is just iterating over each of the
    //! types it contains, as if it were a `Sequence`.
    //! @include example/ext/brigand/list/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! A Brigand list can be searched as if it were a tuple containing
    //! `hana::type`s.
    //! @include example/ext/brigand/list/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! A Brigand list can be created from any `Foldable`. More precisely,
    //! for a `Foldable` `xs` whose linearization is `[x1, ..., xn]`,
    //! @code
    //!     to<ext::brigand::list_tag>(xs) == brigand::list<t1, ..., tn>{}
    //! @endcode
    //! where `tk` is the type of `xk`, or the type contained in `xk` if
    //! `xk` is a `hana::type`.
    //! @include example/ext/brigand/list/conversion.cpp
    template <typename ...T>
    struct list { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace brigand {
        struct list_tag { };
    }}

    template <typename ...T>
    struct tag_of<brigand::list<T...>> {
        using type = ext::brigand::list_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::brigand::list_tag, ext::brigand::list_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const&, Ys const&) {
            return hana::bool_<std::is_same<Xs, Ys>::value>{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::brigand::list_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c<brigand::size<Xs>::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::brigand::list_tag> {
        template <typename Ts, typename N>
        static constexpr auto apply(Ts const&, N const&) {
            constexpr std::size_t n = N::value;
            using T = brigand::at_c<Ts, n>;
            return hana::type<T>{};
        }
    };

    template <>
    struct drop_front_impl<ext::brigand::list_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs const&, std::index_sequence<i...>) {
            return brigand::list<brigand::at_c<Xs, n + i>...>{};
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs const& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = brigand::size<Xs>::value;
            return drop_front_helper<n>(xs,
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::brigand::list_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&)
        { return hana::bool_<brigand::size<Xs>::value == 0>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Conversion from a Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct to_impl<ext::brigand::list_tag, F, when<hana::Foldable<F>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            auto list_type = hana::unpack(xs, hana::template_<brigand::list>);
            return typename decltype(list_type)::type{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BRIGAND_LIST_HPP
