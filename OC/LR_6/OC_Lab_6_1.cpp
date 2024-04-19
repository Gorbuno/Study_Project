#include <unistd.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>           
#include <sys/stat.h> 
#include <iostream>
#include <sys/mman.h>
#include <string.h>


using namespace std;

/*СТАНДАРТ POSIX*/


int main() {
	cout << "Main started\n";
	const char * sem_name_read = "/semread";/*объявить идентификатор семафора чтения;*/
	const char * sem_name_write = "/semwrite";/*объявить идентификатор семафора записи;*/
	int memopen;/*объявить идентификатор разделяемой памяти;*/
	char * addr;/*объявить локальный адрес;*/
	const char *shm_name = "my_shared_memory";
	int SIZE = 4;
	
	struct epoll_event MyEvent;
	int epoll_id;
	int MyEventCount = 0;
	
	MyEvent.events = EPOLLIN;
	MyEvent.data.fd = 0;

	memopen = shm_open(shm_name, O_CREAT | O_RDWR, 0777);
	if (memopen == -1){
		perror("Error shm_open:");
		return 1;
	}
	
	if (ftruncate(memopen, SIZE)  == -1){
		perror("Error ftruncate:");
		return 1;
	}

	addr = (char *) mmap(NULL, SIZE, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_SHARED , memopen, 0);
	if ( addr == (char *) -1){
        	perror ("Error mmap:");
        	return 1;
    	}
	
	sem_t* sem_read = sem_open(sem_name_read, O_CREAT, S_IRWXU, 0);
	sem_t* sem_write = sem_open(sem_name_write, O_CREAT, S_IRWXU, 0);

	if (sem_read == SEM_FAILED || sem_write == SEM_FAILED) {
		printf("Sem error: %s\n", strerror(errno));
		return 1;
	}
	
	epoll_id = epoll_create1(0);
	if ( epoll_id == -1)
	{
		perror("Error epoll_id:");
		return 1;
	}
	
	if( epoll_ctl(epoll_id, EPOLL_CTL_ADD,0,&MyEvent))
	{
		perror("Error epoll_ctl:");
		return 1;
	}
	
	
	int n;
	cout<< "Writing session began. To exit press Enter\n";
	
	while (1){
		MyEventCount = epoll_wait(epoll_id, &MyEvent, 1, 0);
		if(MyEventCount == 1)
		{
			printf("Key was pressed. Program will be closed now\n");
			break;
		}	
		n = getdtablesize();
		if(write(memopen, &n, SIZE)!=SIZE){
			perror("Error with write");
			return 1;
		}
		printf("Wrote value = %d\n", n);
		sem_post(sem_write);
		sem_wait(sem_read);
		sleep(1);
	}

	if (munmap(addr, SIZE)==-1){
		perror ("Error munmap:");
		return 1;
	}
	
	if(shm_unlink(shm_name) == -1){
		perror("Error shm_unlink:");
		return 1;
	}
	if(close(memopen) == -1){
		perror("Error close:");
		return 1;
	}	
	if (close(epoll_id)==-1)
	{
		perror("Error epoll closing:");
		return 1;
	}
	if(sem_close(sem_write) == -1){
		perror("Error sem_close_write:");
		return 1;
	}
	if(sem_close(sem_read) == -1){
		perror("Error sem_close_read:");
		return 1;
	}
	if(sem_unlink(sem_name_write) == -1){
		perror("Error sem_unlink_write:");
		return 1;
	}
	if(sem_unlink(sem_name_read) == -1){
		perror("Error sem_unlink_read:");
		return 1;
	}
	cout << "Writing program is closing now\n";
	return 0;
	}


