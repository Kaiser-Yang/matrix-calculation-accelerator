#ifndef MCA_IDENTITY_MATRIX_H
#define MCA_IDENTITY_MATRIX_H

namespace mca {
// non-copyable, non-movable, non-assignable
struct _IdentityMatrix {
    _IdentityMatrix(_IdentityMatrix &&other)            = delete;
    _IdentityMatrix(const _IdentityMatrix &other)       = delete;
    _IdentityMatrix &operator=(const _IdentityMatrix &) = delete;
    _IdentityMatrix &operator=(_IdentityMatrix &&)      = delete;

    //static method to get the identity matrix
    inline static const _IdentityMatrix &getInstance() {
        static const _IdentityMatrix instance;
        return instance;
    }       
private:
    //private constructor to prevent instantiation
    _IdentityMatrix() = default;
};

inline const _IdentityMatrix & IdentityMatrix() {
    return _IdentityMatrix::getInstance();
}
}  // namespace mca
#endif
