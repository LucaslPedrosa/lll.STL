#pragma once

#include <concepts>

namespace lll::algebra
{


// Default algebraic law declarations.
//
// These flags are not proofs.
// They are explicit mathematical promises made by the type author.
//
// C++ can check the syntax:
//   operation(a, b) returns value_type
//   identity() returns value_type
//
// C++ cannot generally prove semantic laws such as:
//   operation(a, operation(b, c)) == operation(operation(a, b), c)
//   operation(identity(), a) == a
//   operation(a, identity()) == a

template <typename>
struct algebra_traits
{
  static constexpr bool associative = false;
  static constexpr bool commutative = false;
  static constexpr bool idempotent = false;
  static constexpr bool has_identity = false;
};


// Magma:
// A set M equipped with a closed binary operation.
//
// Law:
//   for all a, b in M:
//     a * b is also in M
//
// C++ approximation:
//   M::value_type exists
//   M::operation(value_type, value_type) -> value_type
template <typename M>
concept Magma = requires(typename M::value_type a, typename M::value_type b) {
  typename M::value_type;
  { M::operation(a, b) } -> std::same_as<typename M::value_type>;
};


// Semigroup:
// A magma whose operation is associative.
// Magma + Associativity
//
//
// Law:
// A * (B * C) === (A * B) * C
//
// This law is not checked by the concept.
// The concept only checks the syntactic interface inherited from Magma.
template <typename S>
concept Semigroup = Magma<S>;


// Monoid:
// A semigroup with an identity element.
//
//
// Laws:
//   e * a == a
//   a * e == a
//
// in C++:
//   operation(identity(), a) == a
//   operation(a, identity()) == a
//
// This law is not checked by the concept.
// The concept only checks that identity() exists and returns value_type.
template <typename M>
concept Monoid = Semigroup<M> && requires {
  { M::identity() } -> std::same_as<typename M::value_type>;
};


} // namespace lll::algebra
