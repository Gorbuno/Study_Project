
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <mutex>

#define BUFFER_SIZE 1024
using namespace std;

int Socket;
mqd_t mqid;
int RequestClientFlag = 0;
int ResponceServerFlag = 0;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
socklen_t len = sizeof(client_address);
pthread_mutex_t my_mutex;
char *lastResponsed;

static void *RequestClient(void *arg) { // получение запроса
    int number;
    while (RequestClientFlag == 0) {
        recvfrom(Socket, &number, sizeof(number), 0, (sockaddr *) &client_address,
                 &len);

        /*if (n == -1 && errno == EAGAIN){
            usleep(10000); // пауза на 10 миллисекунд
            continue;}
        /*else if (n == 1) {
            perror ("Recvfrom");
            RequestClientFlag = 1;
            ResponceServerFlag = 1;
            pthread_exit ((void *) 15);}*/
        if (number != 0) {
            pthread_mutex_lock(&my_mutex);
            mq_send(mqid, (char *) &number, sizeof(number), 0);
            cout << "Request " << number << endl;
            fflush(stdout);
            pthread_mutex_unlock(&my_mutex);
        }

        sleep(1);
    }
    pthread_exit((void *) 1);
}

static void *ResponseServer(void *arg) { // отправка ответа
    char buffer[BUFFER_SIZE];
    while (ResponceServerFlag == 0) {
        int number = 0;
        pthread_mutex_lock(&my_mutex);
        int n = sizeof(buffer);

        mq_receive(mqid, (char *) &number, sizeof(number), nullptr);
        pthread_mutex_unlock(&my_mutex);


        if (number != 0) {
            int result = getdtablesize();
            snprintf(buffer, BUFFER_SIZE, "%d", result); // записываем ответ в буфер
            cout << "Answer " << number << ": " << buffer << endl;//вывести результат на экран;
            fflush(stdout);

            socklen_t len;
            len = sizeof(client_address);
            if (sendto(Socket, (const char *) buffer, strlen(buffer), MSG_CONFIRM,
                       (struct sockaddr *) &client_address,
                       len) == -1) {
                cout << "client offline" << endl;
            }
        }
        sleep(1);
    }
    pthread_exit((void *) 2);
}


int main() {
    cout << "Main Server started\n";
    pthread_t idRequestClient, idResponceServer;
    int ExitRequestClient;
    int ExitResponceServer;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(7000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    memset(&client_address, 0, sizeof(client_address));

    struct mq_attr my_attr;
    my_attr.mq_flags = 0;
    my_attr.mq_maxmsg = 1;
    my_attr.mq_msgsize = sizeof(int);
    my_attr.mq_curmsgs = 0;

    cout << "Initializing mutex\n";
    pthread_mutex_init(&my_mutex, NULL);

    cout << "Created Socket\n";
    if ((Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { ;//создать сокет;
        perror("Error server Socket:");
        return 1;
    }

    fcntl(Socket, F_SETFL, O_NONBLOCK);//снятие блокировок с сокетов
    int optval = 1;

    cout << "Binding Socket\n";
    if (setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("Error setsockopt:");
        return 1;
    }
    if (bind(Socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) { //привязать сокет к адресу;
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    cout << "Creating message queue	\n";
    if ((mqid = mq_open("/MyQueue", O_CREAT | O_RDWR | O_NONBLOCK, S_IWUSR | S_IRUSR, &my_attr)) == (mqd_t) -1) {
        perror("Error mq_open:");
        return 1;
    }

    cout << "Creating stream of Request Client\n";
    pthread_create(&idRequestClient, nullptr, RequestClient, nullptr);
    cout << "Creating stream of Responce Server\n";
    pthread_create(&idResponceServer, nullptr, ResponseServer, nullptr);

    cout << "\nThe program is waiting for a keystroke\n";
    getchar();//ждать нажатия клавиши;
    cout << "\nKey pressed\n";

    RequestClientFlag = 1;
    ResponceServerFlag = 1;

    cout << "Closing stream of Request Client\n";
    pthread_join(idRequestClient, (void **) &ExitRequestClient);
    cout << "Closing stream of Responce Server\n";
    pthread_join(idResponceServer, (void **) &ExitResponceServer);

    cout << "\n\n ExitRequestClient = " << ExitRequestClient << endl;
    cout << " ExitResponceServer = " << ExitResponceServer << "\n\n\n";

    cout << "Destroying mutex\n";
    pthread_mutex_destroy(&my_mutex);
    cout << "Closing messege queue\n";
    mq_close(mqid);
    cout << "Unlinking message queue\n";
    mq_unlink("/MyQueue");

    cout << "Closing Socket\n";
    close(Socket);//закрыть сокет

    cout << "\nthe program has ended\n";
    return 0;
}
	s
