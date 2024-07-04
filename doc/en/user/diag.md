# mca::_Diag
```c++
/* Defined in <mca/diag.h> */
template <class Container> _Diag;
```

## Member types
|           |   |
| -         | - |
| size_type | std::size_t |

## Member functions
### Constructors
|                                         |   |
| -                                       | - |
| <nobr>`_Diag(const Container &)`</nobr> | Construct from a container. |
| <nobr>`_Diag(Container &&)`</nobr>      | Construct from a container. |

NOTE: You should not use `_Diag` to construct, you should use the
[helper functions](#helper-functions) to construct.

### Operators
|                                                                                     |   |
| -                                                                                   | - |
| <nobr>`const typename Container::value_type &operator[](const size_type &i)`</nobr> | Return the i-th element of the container. |

### Other
|                                 |   |
| -                               | - |
| <nobr>`size_type size()`</nobr> | Return the size of the container. |

## Helper functions
|                                                                                           |   |
| -                                                                                         | - |
| <nobr>`_Diag<std::decay_t<Container>> Diag(Container &&container)`</nobr>                 | Return a `mca::_Diag` from a container. |
| <nobr>`_Diag<std::initializer_list<T>> Diag(std::initializer_list<T> &&container)`</nobr> | Return a `mca::_Diag` from a `std::initializer_list`. |


[Back to the `mca::Matrix`](matrix.md)

[Back to the `mca::Shape`](shape.md)

[Next: `mca::_IdentityMatrix`](identityMatrix.md)

[Back to the index](index.md)
