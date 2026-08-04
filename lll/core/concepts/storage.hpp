#include <concepts>
#include <cstddef>
namespace lll::concepts
{

template <typename C, typename T>
concept ReadableStorage = requires(const C c, size_t i) {
  { c[i] } -> std::convertible_to<T>;
};

template <typename C, typename T>
concept WritableStorage = requires(const C c, size_t i, T value) {
  c[i] = value;
  { c[i] } -> std::same_as<T>;
};

template <typename C, typename T>
concept MutableStorage = ReadableStorage<C, T> && WritableStorage<C, T>;

} // namespace lll::concepts
