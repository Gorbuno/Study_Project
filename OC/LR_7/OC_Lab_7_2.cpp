#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;
typedef struct {
	long mtype;
	char buff[256];
}TMessage;
size_t flag=0;//объявить флаг завершения потока;
int msgid;//объявить идентификатор очереди сообщений;
char * addr;


static char buf[12];
static void * proc1( void * arg)//Функция потока()
{
	cout << "\nproc1 started\n";
	TMessage message;
	message.mtype = 1;
	size_t len;
	int result;
while( flag == 0)//пока (флаг завершения потока не установлен)
{
	memset(message.buff,0,sizeof(message.buff));//очистить буфер сообщения;
	result = msgrcv(msgid, &message, sizeof(message.buff), message.mtype, IPC_NOWAIT);//принять сообщение из очереди сообщений в буфер;
	cout << "Reseve messege: "<< message.buff<<endl;/*вывести сообщение на экран;*/
	sleep(1);//задержать на время 1 сек;
}
 cout << "\nthe proc1 has ended\n";
        pthread_exit((void*)1);
}
int main ()//основная программа()
{
	pthread_t id;//объявить идентификатор потока;
	int * exitcode;
	key_t key = ftok("test",'Z');
//создать (или открыть, если существует) очередь сообщений;
	msgid = msgget(key,0);//открываем
	if (msgid < 0) {//ошибка открытия
		msgid = msgget(key, IPC_CREAT | 0777);//создаем
	}
	pthread_create(&id, NULL, proc1, &flag);//создать поток из функции потока;
	cout << "\nThe program is waiting for a keystroke\n";
	getchar();//ждать нажатия клавиши;
	cout << "\nKey pressed\n";
    	flag = 1;//установить флаг завершения потока;
	pthread_join(id, (void**)&exitcode);//ждать завершения потока;
	msgctl(msgid, IPC_RMID, NULL);//удалить очередь сообщений;
	
	cout << "exitcode = " << exitcode<<endl;
	cout << "\nthe program has ended\n";
    return 0;
}
