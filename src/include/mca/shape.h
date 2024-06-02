#ifndef MCA_SHAPE_H
#define MCA_SHAPE_H

#include <cstddef>

namespace mca {
struct Shape {
    using size_type   = std::size_t;
    size_type rows    = 0;
    size_type columns = 0;

    inline Shape() = default;

    inline explicit Shape(const size_type &rows, const size_type &columns)
        : rows(rows), columns(columns) {}

    inline bool operator==(const Shape &other) const noexcept {
        return rows == other.rows && columns == other.columns;
    }

    inline bool operator!=(const Shape &other) const noexcept { return !(*this == other); }

    inline size_type size() const noexcept { return rows * columns; };
};
}  // namespace mca
#endif
