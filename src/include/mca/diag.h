#ifndef MCA_DIAG_H
#define MCA_DIAG_H

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace mca {
// non-movable, non-copyable, non-assignable
template <class Container>
class _Diag {
public:
    using size_type = std::size_t;

    _Diag() = delete;

    _Diag(_Diag &&other) noexcept = delete;
    _Diag(const _Diag &other)     = delete;

    _Diag &operator=(const _Diag &) = delete;
    _Diag &operator=(_Diag &&)      = delete;

    inline explicit _Diag(const Container &other) : _diagRef(other) {}
    inline explicit _Diag(Container &&other) : _diag(std::move(other)), _diagRef(_diag) {}

    inline const typename Container::value_type &operator[](const size_type &i) const {
        return std::data(_diagRef)[i];
    }

    inline size_type size() const noexcept { return _diagRef.size(); }

private:
    const Container &_diagRef;
    Container _diag;
};

template <class Container>
inline _Diag<std::decay_t<Container>> Diag(Container &&container) {
    return _Diag<std::decay_t<Container>>(std::forward<Container &&>(container));
}

template <class T>
inline _Diag<std::initializer_list<T>> Diag(std::initializer_list<T> &&container) {
    return _Diag<std::initializer_list<T>>(std::forward<std::initializer_list<T> &&>(container));
}
}  // namespace mca
#endif
