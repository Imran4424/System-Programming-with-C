# What is pthread?

pthreads stands for POSIX threads (Portable Operating System Interface) which is a standard C API for creating and controlling threads on Unix-like systems (Linux, macOS, BSD). In C++, we can still use it directly through the header:

```cpp
#include <pthread.h>
```

pthreads (POSIX threads) is a widely used standard C language API for implementing multithreading. Since pthreads can not run on non-Unix Operating Systems, C++ 11 introduced it's own library `<thread>` which can implement multi-threading in platform independent manner (it can run on any Operating Systems).

Even today pthreads remains a powerful, lower-level, and highly compatible option, especially when interfacing with existing C codebases or requiring specific system-level control.

### Why do we use it?

The primary reasons for using pthreads are to introduce concurrency and parallelism into a program:

- **Performance:** By executing tasks concurrently, applications can better utilize multi-core processors, leading to faster execution times for compute-intensive operations.
- **Responsiveness:** In applications like user interfaces or servers, threads allow one part of the program to handle a long-running operation (e.g., fetching data from a network) without blocking the main program loop, keeping the application responsive.
- **System Control:** As a mature, C-based standard, pthreads offers granular control over thread properties (like scheduling priority and stack size) that may not be as readily exposed in the higher-level C++11 `<thread>` library.

# How to create a pthread

Firstly, we need to  include `<pthread.h>` header in our C/C++ code.

Secondly, we need to create a thread with `pthread_create()`, and then waiting for that thread to complete its work using `pthread_join()`.