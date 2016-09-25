/*
 * lock.h
 *
 *  Created on: Dec 24, 2013
 *      Author: rajtendulkar
 */

#ifndef LOCK_H_
#define LOCK_H_

#include <iostream>
#include <stdint.h>
#include <pthread.h>
#include <sys/types.h>
#include <shared_defs.hpp>

using namespace std;

typedef pthread_mutex_t mutex_t;
#define mutex_init(a,b) pthread_mutex_init(a,b)
#define mutex_destroy(a) pthread_mutex_destroy(a)
#define mutex_lock(a) pthread_mutex_lock(a)
#define mutex_unlock(a) pthread_mutex_unlock(a)

#endif /* LOCK_H_ */
