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

```cpp
#include <iostream>
#include <pthread.h>
#include <unistd.h> // For sleep()

using namespace std;

// This function is executed by the new thread
void* print_message(void* data) {
    string message = *((string*) data);
    cout << "Thread ID: " << pthread_self() << ". Message: " << message << endl;
    sleep(1); // Simulate some work
    cout << "Thread " << pthread_self() << " finished." << endl;
    pthread_exit(NULL); // Optional: explicitly exit the thread
}

int main() {
    pthread_t thread_id;
    string msg = "Hello from a new thread!";
    int rc;

    cout << "Main program starting. Main Thread ID: " << pthread_self() << endl;

    // Create the thread:
    // 1st arg: address of pthread_t variable
    // 2nd arg: thread attributes (NULL for default)
    // 3rd arg: pointer to the function to execute (thread entry point)
    // 4th arg: arguments to pass to the function (must be a void* pointer)
    rc = pthread_create(&thread_id, NULL, print_message, &msg);

    if (rc) {
        cerr << "Error: unable to create thread, return code: " << rc << endl;
        return 1;
    }

    // Main thread waits for the newly created thread to finish
    pthread_join(thread_id, NULL);

    cout << "Main program exiting." << endl;

    return 0;
}
```

### Key functions to remember

- `pthread_create()`: Starts a new thread, pointing to a specific function
- `pthread_join()`: Blocks the calling thread (e.g., main) until the specified target thread terminates. This ensures synchronization
- `pthread_exit()`: Terminates the calling thread.
- `pthread_self()`: Returns the ID of the current thread.

