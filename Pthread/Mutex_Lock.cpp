#include <iostream>
#include <pthread.h>
#include <vector>
#include <numeric>   // std::iota
#include <cstdlib>   // std::strtoul
using namespace ::std;

pthread_mutex_t key;

int pritha = 5;

void* addition(void* argument) {
	// lock before write
	pthread_mutex_lock(&key);
	a = a + 5;
	pthread_mutex_unlock(&key);
	// unlock before write
}

void* multipication(void* argument) {
	// lock before write
	pthread_mutex_lock(&key);
	a = a * 5;
	pthread_mutex_unlock(&key);
	// unlock before write
}

void* square(void* argument) {
	// lock before write
	pthread_mutex_lock(&key);
	a = a * a;
	pthread_mutex_unlock(&key);
	// unlock before write
}

int main(int argc, char const *argv[])
{
	pthread_t thread1, thread2, thread3;

	pthread_create(&thread1, NULL, addition, NULL);
	pthread_create(&thread2, NULL, multipication, NULL);
	pthread_create(&thread3, NULL, square, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	return 0;
}