
#ifndef GENERATOR_H
#define GENERATOR_H

#include <coroutine>
#include <exception>
#include <ranges>
#include <utility>

namespace smartled
{
template<typename T>
class Generator;

namespace details
{
  template<typename T>
  struct GeneratorPromise
  {
    using value_type = std::remove_reference_t<T>;
    using reference_type = std::add_lvalue_reference_t<value_type>;
    using pointer_type = std::add_pointer_t<value_type>;

    T _value;

    GeneratorPromise() noexcept = default;

    Generator<T> get_return_object() noexcept;

    constexpr std::suspend_always yield_value(T value) noexcept
    {
      _value = value;
      return {};
    }

    // clang-format off

    constexpr std::suspend_always initial_suspend() const noexcept { return {}; }
    constexpr std::suspend_always final_suspend() const noexcept { return {}; }

    constexpr void unhandled_exception() noexcept { std::terminate(); }

    constexpr void return_void() noexcept {}

    // clang-format on

    template<typename U>
    std::suspend_never await_transform(U&& value) = delete;
  };

  // TODO use sentinel

  template<typename T>
  class GeneratorIterator
  {
  private:
    using CoroutineHandle = std::coroutine_handle<GeneratorPromise<T>>;

  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = typename GeneratorPromise<T>::value_type;
    using reference = typename GeneratorPromise<T>::reference_type;
    using pointer = typename GeneratorPromise<T>::pointer_type;

    constexpr GeneratorIterator() noexcept : _handle(nullptr), _done(false) {};

    constexpr GeneratorIterator(CoroutineHandle handle, bool done) noexcept : _handle(handle), _done(done) {}

    GeneratorIterator& operator++()
    {
      _handle.resume();
      _done = _handle.done();
      return *this;
    }

    constexpr bool operator==(const GeneratorIterator& other) const noexcept
    {
      return _done == other._done;
    }

    constexpr bool operator!=(const GeneratorIterator& other) const noexcept
    {
      return !(*this == other);
    }

    // clang-format off

    void operator++(int) { (void)operator++(); }

    reference operator*() const noexcept { return _handle.promise()._value; }
    pointer operator->() const noexcept { return std::addressof(operator*()); }

    // clang-format on

  private:
    CoroutineHandle _handle;
    bool _done;
  };
} // namespace details

template<typename T>
class Generator
{
public:
  using promise_type = details::GeneratorPromise<T>;
  using iterator = details::GeneratorIterator<T>;

  constexpr Generator() noexcept : _handle(nullptr) {}

  constexpr Generator(Generator&& other) noexcept : _handle(other._handle)
  {
    other._handle = nullptr;
  }

  Generator(const Generator&) = delete;

  ~Generator()
  {
    if (_handle)
    {
      _handle.destroy();
    }
  }

  Generator& operator=(Generator other) noexcept
  {
    swap(other);
    return *this;
  }

  iterator begin()
  {
    _handle.resume();
    return { _handle, _handle.done() };
  }

  iterator end() noexcept
  {
    return { _handle, true };
  }

  void swap(Generator& other) noexcept
  {
    std::swap(_handle, other._handle);
  }

private:
  friend class details::GeneratorPromise<T>;

  explicit Generator(std::coroutine_handle<promise_type> handle) noexcept : _handle(handle) {}

  std::coroutine_handle<promise_type> _handle;
};

namespace details
{
  template<typename T>
  Generator<T> GeneratorPromise<T>::get_return_object() noexcept
  {
    using CoroutineHandle = std::coroutine_handle<GeneratorPromise<T>>;
    return Generator<T> { CoroutineHandle::from_promise(*this) };
  }
} // namespace details

} // namespace smartled

#endif