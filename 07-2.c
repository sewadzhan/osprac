
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int tmp = 0;
void *mythread(void *dummy)
{
	pthread_t my_thid;
	my_thid = pthread_self();
	tmp = tmp + 1;
	printf("Thread %d, Calculation result = %d\n", my_thid, tmp);
	return NULL;
}

int main()
{
	  pthread_t th_id1, th_id2, myth_id;
	  int result;

	  result = pthread_create( &th_id1, (pthread_attr_t *)NULL, mythread, NULL);
	  if (result != 0) {
	    printf ("Error on thread create (second thread), return value = %d\n", result);
	    exit(-1);
	  }
	  printf("Second thread created, th_id1 = %d\n", th_id1);

	  result = pthread_create( &th_id2, (pthread_attr_t *)NULL, mythread, NULL);

	  if (result != 0) {
	    printf ("Error on thread create (third thread), return value = %d\n", result);
	    exit(-1);
	  }

	  printf("Third thread created, th_id2 = %d\n", th_id2);

	  myth_id = pthread_self();
	  tmp = tmp + 1;
	  printf("Thread %d, Calculation result = %d\n", myth_id, tmp);

	  pthread_join(th_id1, (void **)NULL);
	  pthread_join(th_id2, (void **)NULL);

	  return 0;
}
