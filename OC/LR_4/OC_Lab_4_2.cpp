#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <signal.h>

#define SEM_NAME "/semofore"

using namespace std;

int main() {
    fd_set rfds;
    sigset_t signmask;
    int p_sel;
    int file;
    int flag = 0;
    const void *sym = "2";
    cout << "\nmain started\n";

    struct timespec tv;
    tv.tv_nsec = 0;
    tv.tv_sec = 0;

    sem_t *our_sem;  /*объявить идентификатор именованного семафора;*/
    sigemptyset(&signmask);
    sigaddset(&signmask, SIGTTIN);

    if ((our_sem = sem_open(SEM_NAME, O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror("Error sem_open");
        return -1;
    }

    file = open("test.txt", O_CREAT | O_WRONLY, 0644);/*создать (или открыть, если существует) файл;*/
    if (file == -1) {
        cout << "error open file" << endl;
        return -1;
    }
    cout << "\nThe program is waiting for a keystroke\n";
    while (flag == 0) {
        
    FD_ZERO(&rfds);// опустощает набор
    FD_SET(0, &rfds);// добавляет значение файлового дескриптора в набор

    if (sigprocmask(SIG_BLOCK, &signmask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
        //захватить именованный семафор;
        int sem_taling_result = sem_wait(our_sem);
        if (sem_taling_result != 0) {
            perror("Error sem_wait");
            return -1;
        }
        for (int i = 0; i < 2; i++) {
            lseek(file, 0, SEEK_END);
            write(file, sym, 1);
            cout << "2";
            fflush(stdout);
            sleep(1);
        }
        if (sem_post(our_sem) != 0) perror("Error sem_post"); //освободить именованный семафор;
        sleep(1);

        p_sel = pselect(file + 1, &rfds, NULL, NULL, &tv, &signmask);
        switch (p_sel) {
            case -1:
                cout << "Error in pselect";
                break;
            case 0:
                flag = 0;
                continue;
            default:
                flag = 1;
                break;
        }
    }
    cout << "\nKey pressed\n";
    close(file);    /*закрыть файл;*/
    sem_close(our_sem);  /*закрыть именованный семафор;*/
    sem_unlink(SEM_NAME); /*удалить именованный семафор;*/


    cout << "\nthe program has ended\n";
    return 0;
}

