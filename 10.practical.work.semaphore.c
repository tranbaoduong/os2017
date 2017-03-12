#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 10

typedef struct {
	char type; 
	int amount;
	char unit; 
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t s; //define semaphore

int sem_wait(sem_t *sem);

int sem_post(sem_t *sem);

int sem_init(sem_t *sem, int pshared, unsigned int value);

int sem_destroy(sem_t *sem);

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
  sem_wait(&s);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
  sem_post(&s);
}

item *consume() {
	item *i = (item *)malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
  sem_wait(&s);
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	sem_post(&s);
  return i;
 }

void firstlast() {
	printf("First = %d  Last = %d\n",first,last);
}

void *producethread(void *param){
	item item1;
	item item2;
	item item3;

	item1.type = '10';
	item1.amount = 0;
	item1.unit = '10';

	item2.type = '0';
	item2.amount = 5;
	item2.unit = '0';

	item3.type = '3';
	item3.amount = 3;
	item3.unit = '0';

	printf("Producing item 1: type=%c amount=%d unit=%c\n",
	item1.type, item1.amount, item1.unit);
	produce(&item1);
	firstlast();

	printf("Producing item 2: type=%c amount=%d unit=%c\n",
	item2.type, item2.amount, item2.unit);
	produce(&item2);
	firstlast();

	printf("Producing item 3: type=%c amount=%d unit=%c\n",
	item3.type, item3.amount, item3.unit);
	produce(&item3);
	firstlast();
}

void *consumethread(void *param) {
	printf("After consume the first item:\n");
	consume();
	firstlast();

	printf("After consume the second item:\n");
	consume();
	firstlast();
}

int main() {
  sem_init(&s, 0, 1); //init semaphore
  pthread_t tid1, tid2;
	
  pthread_create(
		&tid1,
		NULL,
		producethread,
		NULL);
  pthread_join(tid1, NULL);

	pthread_create(
		&tid2,
		NULL,
		consumethread,
		NULL);
  pthread_join(tid2, NULL);
  
  sem_destroy(&s); //destroy semaphore
}
