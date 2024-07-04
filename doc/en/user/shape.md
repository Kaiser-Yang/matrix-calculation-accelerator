# mca::Shape
```c++
/* Defined in header file <mca/shape.h> */
struct Shape;
```

## Member types
|           |   |
| -         | - |
| size_type | std::size_t |

## Member variables
|                        |   |
| -                      | - |
| <nobr>`rows`</nobr>    | The number of rows. |
| <nobr>`Columns`</nobr> | The number of columns. |

## Member functions
### Constructors
|                                                                       |   |
| -                                                                     | - |
| <nobr>`Shape()`</nobr>                                                | Construct a (0, 0) shape. |
| <nobr>`Shape(const size_type &rows, const size_type &columns)`</nobr> | Construct a (rows, columns) shape. |
| <nobr>`Shape(const Shape &)`</nobr>                                   | Copy constructor. |
| <nobr>`Shape(Shape &&)`</nobr>                                        | Move constructor. |

### Operators
|                                                |   |
| -                                              | - |
| <nobr>`Shape &operator=(const Shape &)`</nobr> | Copy assignment. |
| <nobr>`void operator=(Shape &&)`</nobr>        | Move assignment. |
| <nobr>`bool operator==(const Shape &)`</nobr>  | Return `true` if two shapes are same, otherwise `false`. |
| <nobr>`bool operator!=(const Shape &)`</nobr>  | Return `true` if two shapes are not same, otherwise `false`. |

### Other
|                                 |   |
| -                               | - |
| <nobr>`size_type size()`</nobr> | Return the size of a shape. |

[Back to the `mca::Matrix`](matrix.md)

[Next: `mca::_Diag`](diag.md)

[Back to the index](index.md)
