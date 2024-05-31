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
    _Diag() = delete;

    _Diag(_Diag &&other) noexcept = delete;
    _Diag(const _Diag &other)     = delete;

    _Diag &operator=(const _Diag &) = delete;
    _Diag &operator=(_Diag &&)      = delete;

    inline explicit _Diag(const Container &other);
    inline explicit _Diag(Container &&other);

    inline const typename Container::value_type &operator[](const size_t &i) const;
    inline size_t size() const;

private:
    const Container &_diagRef;
    Container _diag;
};

template <class Container>
_Diag<Container>::_Diag(const Container &_diag) : _diagRef(_diag) {}

template <class Container>
inline _Diag<Container>::_Diag(Container &&_diag) : _diag(std::move(_diag)), _diagRef(_diag) {}

template <class Container>
inline const typename Container::value_type &_Diag<Container>::operator[](const size_t &i) const {
    return std::data(_diagRef)[i];
}

template <class Container>
inline size_t _Diag<Container>::size() const {
    return _diagRef.size();
}

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
