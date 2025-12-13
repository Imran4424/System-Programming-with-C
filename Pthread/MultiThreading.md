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
    int creationStatus;

    cout << "Main program starting. Main Thread ID: " << pthread_self() << endl;

    // Create the thread:
    // 1st arg: address of pthread_t variable
    // 2nd arg: thread attributes (NULL for default) (these argument can set scheduling policy)
    // 3rd arg: pointer to the function to execute (thread entry point)
    // 4th arg: arguments to pass to the function (must be a void* pointer)
    creationStatus = pthread_create(&thread_id, NULL, print_message, &msg);
    // after creation thread starts to run immediately.

    if (creationStatus) {
        cerr << "Error: unable to create thread, return code: " << creationStatus << endl;
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

```cpp
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <array>
#include <string>

using namespace std;

const int NUM_THREADS = 5;

// Structure to pass multiple arguments to the thread function
struct ThreadData {
    int thread_id;
    string message;
};

// This function is executed by all new threads
void* worker_thread(void* arg) {
    ThreadData *data = static_cast<ThreadData*>(arg);

    cout << "[Thread " << data->thread_id << "] starting execution. Message: \"" << data -> message << "\"" << endl;

    // Simulate some variable work time based on the thread ID
    sleep(NUM_THREADS - data -> thread_id + 1);

    cout << "[Thread " << data -> thread_id << "] finished its work and exiting." << endl;
    
    // We don't need pthread_exit() here if the function returns naturally,
    // but it can be used for explicit control: pthread_exit(NULL);
    return NULL;
}

int main() {
    // Array to hold thread identifiers
    pthread_t threads[NUM_THREADS];
    
    // Array of structures to hold unique data for each thread
    ThreadData td[NUM_THREADS];
    int creationStatus; // Return code holder

    cout << "Main program starting. Preparing to create " << NUM_THREADS << " threads." << endl;

    for (int i = 0; i < NUM_THREADS; ++i) {
        // Prepare the unique data for the current thread
        td[i].thread_id = i;
        td[i].message = "Task " + to_string(i);

        cout << "Main: creating thread " << i << endl;

        // Create the thread, passing a pointer to the unique data structure
        creationStatus = pthread_create(&threads[i], NULL, worker_thread, (void *)&td[i]);

        if (creationStatus) {
            cerr << "Error: unable to create thread, return code: " << creationStatus << endl;
            return 1;
        }
    }

    // The Threads Execute Concurrently (The operating system's scheduler runs them in parallel)
    // upon creation thread starts running immediately
    // And they can run in any order

    // --- Synchronization Point ---
    // The main thread now waits for *all* the created threads to terminate.
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        cout << "Main: Joined with thread " << i << "." << endl;
    }

    cout << "Main program exiting after all threads completed." << endl;

    return 0;
}
```

### How to set priority to thread

Let's look at the synopsis of `pthread_create`

```cpp
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
```

- `pthread_t`: Contains the newly created thread id
- `pthread_attr_t`: Contains newly created thread attributes (Use `NULL` for default attributes.)
    - stack size
    - detach state
    - thread execution policy (in other words priority)
- `void *(*start_routine)(void *)`: pointer to the function the new thread will run. (must match the signature)
- `void *arg`: a single pointer passed to `start_routine`. Commonly a pointer to a struct/object holding multiple values.
- Return values
  - Returns 0 on success
  - Returns a non-zero error number on failure


### Thread scheduling policy

With the help of `pthread_attr_t` we can set Thread scheduling policy for setting execution priority of threads.

There are three main thread policies

#### `SCHED_OTHER` (Default Time-Sharing Policy)

This is the default scheduling policy for most standard, non-real-time applications on Linux and many Unix systems

- **Behavior:** It implements a time-sharing or "fair-share" approach. All threads with this policy are given an opportunity to run.
- **Priorities:** The numeric priority parameter in pthreads is ignored for this policy (it's effectively 0). Instead, the system uses a dynamic priority system based on the thread's "niceness" value (a value from -20 to 19 that influences how much CPU time a process gets), I/O wait time, and CPU usage. The scheduler tries to be fair and responsive, ensuring no thread is completely starved of CPU time.
- **Permissions:** No special permissions are required to use this policy.

#### SCHED_FIFO (First-In, First-Out Real-Time Policy)


Modified code with scheduling thread priority

```cpp
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <sched.h>   // Required for scheduling functions/constants
#include <errno.h>   // For error handling
#include <cstring>   // For strerror

using namespace std;

const int NUM_THREADS = 5;

struct ThreadData {
    int thread_id;
    string message;
};

void* worker_thread(void* arg) {
    ThreadData *data = static_cast<ThreadData*>(arg);
    
    // Optional: Get and print the runtime priority of the running thread
    struct sched_param param;
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &param);
    
    cout << "[Thread " << data->thread_id << "] PID " << getpid() 
         << " running with priority: " << param.sched_priority 
         << " (Policy: " << (policy == SCHED_FIFO ? "FIFO" : (policy == SCHED_RR ? "RR" : "OTHER")) << ")" << endl;

    sleep(1 + data->thread_id); // Longer sleep for lower ID threads to show priority effect

    cout << "[Thread " << data->thread_id << "] finished." << endl;
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData td[NUM_THREADS];
    
    // 1. Initialize Thread Attributes Object
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    // 2. Set the inheritance scope to explicit (essential for setting custom params)
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    
    // Define scheduling parameters structure
    struct sched_param param;

    cout << "Main program starting. " << endl;

    for (int i = 0; i < NUM_THREADS; ++i) {
        td[i].thread_id = i;
        td[i].message = "Task " + to_string(i);

        // 3. Determine the priority value (High for T0, gradually lower for others)
        // This is tricky: SCHED_OTHER uses 'nice' values, SCHED_FIFO uses 1-99 range.
        // We will stick to the default policy and adjust 'nice' behavior if possible,
        // or attempt a real-time priority (which needs root).

        // Example attempting to use real-time priority for demonstration:
        int base_prio = sched_get_priority_min(SCHED_FIFO);
        int priority_to_set = base_prio + (NUM_THREADS - i); // T0 gets prio 5, T4 gets prio 1 (relative)

        param.sched_priority = priority_to_set;

        // 4. Set the scheduling policy and parameter in the attribute object
        // NOTE: SCHED_FIFO generally requires root permissions.
        if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
            cerr << "Warning: Could not set SCHED_FIFO policy. Running with default policy." << endl;
        }
        if (pthread_attr_setschedparam(&attr, &param) != 0) {
            cerr << "Warning: Could not set priority " << priority_to_set << ". Reason: " 
                 << strerror(errno) << endl;
        }

        // 5. Create the thread using the configured attributes
        int creationStatus = pthread_create(&threads[i], &attr, worker_thread, (void *)&td[i]);
        if (creationStatus) {
            cerr << "Error creating thread " << i << ": return code " << creationStatus << endl;
            return 1;
        }
    }

    // Clean up attributes object once all threads are created
    pthread_attr_destroy(&attr);

    // Wait for all threads to join
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    cout << "Main program exiting." << endl;
    return 0;
}
```