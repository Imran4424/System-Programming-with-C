
#include <iostream>
#include <pthread.h>
#include <vector>
#include <numeric>   // std::iota
#include <cstdlib>   // std::strtoul
using namespace ::std;

void* greetings(void* argument) {
	cout << "Hi, Pritha" << endl;

	return NULL;
}

void* reply(void* argument) {
	cout << "Hi, I am good" << endl;

	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, greetings, NULL);
	pthread_create(&thread2, NULL, reply, NULL);


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return 0;
}