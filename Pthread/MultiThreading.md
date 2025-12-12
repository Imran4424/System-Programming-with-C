# What is pthread?

pthreads stands for POSIX threads (Portable Operating System Interface) which is a standard C API for creating and controlling threads on Unix-like systems (Linux, macOS, BSD). In C++, we can still use it directly through the header:

```cpp
#include <pthread.h>
```

pthreads (POSIX threads) is a widely used standard C language API for implementing multithreading. Since pthreads can not run on non-Unix Operating Systems, C++ 11 introduced it's own library `<thread>` which can implement multi-threading in platform independent manner (it can run on any Operating Systems).

Even today pthreads remains a powerful, lower-level, and highly compatible option, especially when interfacing with existing C codebases or requiring specific system-level control.

### Why do we use it?