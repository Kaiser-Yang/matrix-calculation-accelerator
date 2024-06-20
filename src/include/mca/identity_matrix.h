#ifndef MCA_IDENTITY_MATRIX_H
#define MCA_IDENTITY_MATRIX_H

namespace mca {
// non-copyable, non-movable, non-assignable
struct IdentityMatrix {
    inline IdentityMatrix() = default;

    IdentityMatrix(IdentityMatrix &&other)            = delete;
    IdentityMatrix(const IdentityMatrix &other)       = delete;
    IdentityMatrix &operator=(const IdentityMatrix &) = delete;
    IdentityMatrix &operator=(IdentityMatrix &&)      = delete;
};
}  // namespace mca
#endif
