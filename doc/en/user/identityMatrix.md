# mca::_IdentityMatrix
```c++
/* Defined in <mca/identity_matrix.h> */
struct _IdentityMatrix;
```

NOTE: This class is a singleton class. And you should not construct from the `getInstance()`. You should
use the [helper functions](#helper-functions) to get an instance.

## Member functions
|                                                            |   |
| -                                                          | - |
| <nobr>`static const _IdentityMatrix &getInstance()`</nobr> | Return a reference to the singleton instance. |
## Helper functions
|                                                        |   |
| -                                                      | - |
| <nobr>`const _IdentityMatrix &IdentityMatrix()`</nobr> | Return a reference to the singleton instance. |

[Back to the `mca::Matrix`](matrix.md)

[Back to the `mca::_Diag`](diag.md)

[Next: `mca`](mca.md)

[Back to the index](index.md)
