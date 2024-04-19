/**
 * В качестве сообщения необходимо передавать результат выполнения некоторой функции ОС.
 * Функцию следует выбрать из таблицы функций, представленных в конце методических указаний.
 * int getdtablesize(void) - получить размер таблицы дескрипторов;
передать полученное числ
 */

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
using namespace std;

typedef struct{
    int flag;
} targs;
int fd_pair[2]; //объявить идентификатор неименованного канала;
int buff;
static void * proc1( void * arg){
    cout << "\nproc1 started\n";

    targs *args = (targs* ) arg;
    while (args ->flag ==0) {
        buff=getdtablesize(); /* сформировать из данных сообщение в буфере;*/
        if (write (fd_pair[1], &buff, sizeof(buff) == -1)) {
           perror("Error write file:");
           pthread_exit((void *) -1);
       } /*записать сообщение из буфера в неименованный канал;*/
        sleep(1);
    }
    cout << "\nthe proc1 has ended\n";
    pthread_exit((void*)1);
}
static void * proc2( void * arg) {
    cout << "\nproc2 started\n";
    targs *args = (targs *) arg;
    int k;
    while (args ->flag ==0) {
        buff = 0;/*  очистить буфер;*/
        k = read (fd_pair[0], &buff, sizeof (buff));/*прочитать сообщение из неименованного канала в буфер;*/
        if (k==-1) {
            perror("Error read file:");
            pthread_exit((void *) -1);
        }

        cout << buff; /*вывести сообщение на экран;*/

    }
    cout << "\nthe proc2 has ended\n";
    pthread_exit((void*)2);
}
int main (int argc, char * argv[]) {
    cout << "\nmain started\n";
    targs arg1,arg2;
    pthread_t id1,id2;
    arg1.flag = 0;
    arg2.flag = 0;

    if (argc <=1 ) {
        cout << "Restart the program and enter the arguments before starting\nEnter the number of the selected function: \n 1 -- pipe;\n 2 -- pipe2;\n 3 -- pipe with fcntl;\n"<<endl;
        return 0;}
    char * n = argv [1] ;
    switch (*n){
        case '1':
            if (pipe(&fd_pair[2])==-1)
            {
                perror("Error in case 1 -- pipe :");
                exit(EXIT_FAILURE);
            }//    создать неименованный канал;
            if (fcntl(fd_pair[1], F_SETFL, O_NONBLOCK)==-1){
                perror("Error in case 3-- fcntl 1:");
                exit(EXIT_FAILURE);
            };
            if (fcntl(fd_pair[0], F_SETFL, O_NONBLOCK)==-1){
                perror("Error in case 3-- fcntl 2:");
                exit(EXIT_FAILURE);
            };
            break;
        case '2':
            pipe2(&fd_pair[2], O_NONBLOCK);//    создать неименованный канал;
            break;
        case '3':
            if (pipe(&fd_pair[2])==-1)
            {
                perror("Error in case 3-- pipe :");
                exit(EXIT_FAILURE);
            }//    создать неименованный канал;
            break;
        default:
            cout << "You are mistaken. Restart the program"<< endl;
            return 0;
    }


    int * exitcode1;
    int * exitcode2;
    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);
    cout << "\nThe program is waiting for a keystroke\n";
    getchar();
    cout << "\nKey pressed\n";
    arg1.flag = 1;
    arg2.flag = 1;

    pthread_join(id1, (void**)&exitcode1);
    pthread_join(id2, (void**)&exitcode2);

//    закрыть неименованный канал (две операции);
    close (fd_pair[1]);
    close (fd_pair[0]);
    cout << "exitcode1 = " << exitcode1<<endl;
    cout << "exitcode2 = " << exitcode2<<endl;
    cout << "\nthe program has ended\n";
    return 0;
}
