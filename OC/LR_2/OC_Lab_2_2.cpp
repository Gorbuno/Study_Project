#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
using namespace std;
typedef struct {
    int flag;
    char sym;
} targs;
pthread_spinlock_t id_spin;
    int spin_flag = PTHREAD_PROCESS_PRIVATE;
static void *proc1(void *arg) {
    cout << "\nproc1 started\n";
    targs *args = (targs *) arg;

    while (args->flag == 0) {
        if (pthread_spin_trylock(&id_spin) == 0) {
            int k = 0;
            while (k != 10) {
                putchar(args->sym);
                fflush(stdout);
                sleep(1);
                k++;
            }
            pthread_spin_unlock(&id_spin);
            sleep(1);
        }
        else {
        	printf("ERROR: PTHREAD_SPIN_TRYLOCK -- %s\n", strerror(pthread_spin_trylock(&id_spin)));
        	break;
        }
    }
    cout << "\nthe proc1 has ended\n";
    pthread_exit((void *) 1);
}

static void *proc2(void *arg) {
    cout << "\nproc2 started\n";
    targs *args = (targs *) arg;

    while (args->flag == 0) {
        if (pthread_spin_trylock(&id_spin) == 0) {
            int k = 0;
            while (k != 10) {
                putchar(args->sym);
                fflush(stdout);
                sleep(1);
                k++;
            }
            pthread_spin_unlock(&id_spin);
            sleep(1);
        }
        else {
        	printf("ERROR: PTHREAD_SPIN_TRYLOCK -- %s\n", strerror(pthread_spin_trylock(&id_spin)));
        	break;
        }
    }
    cout << "\nthe proc2 has ended\n";
    pthread_exit((void *) 2);
}

int main() {
    cout << "\nmain started\n";
    targs arg1, arg2;
    pthread_t id1, id2;
    if (pthread_spin_init(&id_spin, spin_flag) != 0) {
        cout << "ERROR SPIN_INIT" << endl;
        return 1;
    }
    arg1.flag = 0;
    arg1.sym = '1';
    arg2.flag = 0;
    arg2.sym = '2';
    int *exitcode1;
    int *exitcode2;

    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);

    cout << "\nThe program is waiting for a keystroke\n";
    getchar();
    cout << "\nKey pressed\n";

    arg1.flag = 1;
    arg2.flag = 1;

    pthread_join(id1, (void **) &exitcode1);
    pthread_join(id2, (void **) &exitcode2);
    cout << "exitcode1 = " << exitcode1 << endl;
    cout << "exitcode2 = " << exitcode2 << endl;

    if (pthread_spin_destroy(&id_spin) != 0) {
        cout << "ERROR SPIN_DESTROY" << endl;
        return 2;
    }
    cout << "\nthe program has ended\n";
    return 0;
}

