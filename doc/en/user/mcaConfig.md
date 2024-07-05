# mca configurations
In this part, we will introduce the configurations of the `mca` library.

## Member types
|                          |   |
| -                        | - |
| <nobr>`size_type`</nobr> | <nobr>`std::size_t`</nobr> |

## Configuration
All the configuration methods are defined in `<mca/mca_config.h>`:
|                                                                                                 |   |
| -                                                                                               | - |
| <nobr>`void init(const size_type &threadNum, const size_type &limit, const double &eps)`</nobr> | Initialize the configurations. |
| <nobr>`void setThreadNum(const size_type &threadNum)`</nobr>                                    | Set the number of threads. |
| <nobr>`void setLimit(const size_type &limit)`</nobr>                                            | Set the limit of the number of elements in a matrix. |
| <nobr>`void setEps(const double &eps)`</nobr>                                                   | Set the epsilon. |
| <nobr>`size_type threadNum()`</nobr>                                                            | Get the number of threads. |
| <nobr>`size_type limit()`</nobr>                                                                | Get the limit of the number of elements in a matrix. |
| <nobr>`double eps()`</nobr>                                                                     | Get the epsilon. |
| <nobr>`ThreadPool &threadPool()`</nobr>                                                         | Get the thread pool. |

## Explanations for the configurations
There are three variables you can configure:
* `threadNum`: the number of threads. The default value is
`std::thread::hardware_concurrency() - 1`. The actually number of threads will be `threadNum + 1`
(we always let the main thread to calculate the last part of the calculation).
* `limit`: the minimal limit of calculation every thread will calculate. The default value is `623`.
If the value is set to `0`, the value will be `1` actually.
* `eps`: the epsilon for comparing floating numbers. The default value is `1e-100`.

Suppose `a` and `b` are two floating number, the `eps` works as follows:
* `fabs(a - b) <= eps` means `a` and `b` are equal.
* `fabs(a - b) >  eps` means `a` and `b` are not equal.
* `a - b >   eps` means `a` is greater than `b`.
* `a - b >= -eps` means `a` is greater than or equal to `b`.
* `a - b <  -eps` means `a` is less than `b`.
* `a - b <=  eps` means `a` is less than or equal to `b`.

This part has not been finished yet: add some examples.

[Back to the `mca`](mca.md)

[Back to the index](index.md)
