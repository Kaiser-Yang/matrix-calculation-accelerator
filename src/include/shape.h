#ifndef MCA_SHAP_H
#define MCA_SHAP_H
#include <cstddef>
namespace mca {
struct Shape {
    size_t rows    = 0;
    size_t columns = 0;

    inline Shape() = default;

    inline explicit Shape(size_t rows, size_t columns);

    inline bool operator==(const Shape &other) const;

    inline bool operator!=(const Shape &other) const;

    inline size_t size() const;
};

inline Shape::Shape(size_t rows, size_t columns) : rows(rows), columns(columns) {}

inline bool Shape::operator==(const Shape &other) const {
    return rows == other.rows && columns == other.columns;
}

inline bool Shape::operator!=(const Shape &other) const { return !(*this == other); }

inline size_t Shape::size() const { return rows * columns; }

}  // namespace mca
#endif
