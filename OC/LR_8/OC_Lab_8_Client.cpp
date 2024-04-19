
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

#define BUFFER_SIZE 1024
using namespace std;

int Socket;
int RequestClientFlag = 0;
int ResponceServerFlag = 0;
struct sockaddr_in server_address, client_address = {AF_INET, INADDR_ANY, INADDR_ANY};
int number = 0;

static void* RequestClient (void* arg){ // отправка запроса
	while (RequestClientFlag == 0){
		number ++;
		if (sendto( Socket, &number, sizeof(number), 0, (struct sockaddr*) &server_address, (socklen_t) sizeof(server_address)) == -1){
			perror ("Sendto");
			RequestClientFlag = 1;
			ResponceServerFlag = 1;
			pthread_exit ((void *) 15);} 
		if (number != 0) cout << "Request " << number << endl;
		sleep (1);
	}
	pthread_exit ((void *) 1);
}
static void* ResponceServer (void* arg){ // получение ответа
	char buffer [BUFFER_SIZE];
	while (ResponceServerFlag == 0){
		int n = recvfrom (Socket, &buffer, sizeof(buffer), 0, nullptr, 0);
		if (n == -1 && errno == EAGAIN){
			usleep(10000); // пауза на 10 миллисекунд
			continue;}
		else if (n == -1) {
			perror ("Recvfrom");
			RequestClientFlag = 1;
			ResponceServerFlag = 1;
			pthread_exit ((void *) 15);}
		if (number != 0) cout << "Answer " << number << ": " << buffer << endl;
		sleep (1);
	}
	pthread_exit ((void *) 2);
}


int main(){
	cout << "Main Client started\n";
	pthread_t idResponceServer, idRequestClient;
	int ExitRequestClient;
	int ExitResponceServer;
	
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(7000);
	server_address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	
	cout << "Creating socket\n";
	if ((Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ){;//создать сокет;
		perror ("Error server Socket:");
		return 1;
	}
	fcntl(Socket, F_SETFL, O_NONBLOCK);//снятие блокировок с сокетов
	int optval = 1;
	
	cout << "Binding Socket\n";
	if (setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))==-1)
	{
	    perror("Error setsockopt:");
	    return 1;
	}
	if (bind(Socket,(struct sockaddr*) &client_address, sizeof(client_address)) <0) { //привязать сокет к адресу;
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	cout << "Creating stream of Request Client\n";
	pthread_create(&idRequestClient, nullptr, RequestClient, nullptr);
	cout << "Creating stream of Responce Server\n";	
	pthread_create(&idResponceServer, nullptr, ResponceServer, nullptr);	
	
	cout << "\nThe program is waiting for a keystroke\n";
	getchar();//ждать нажатия клавиши;
	cout << "\nKey pressed\n";
	
	RequestClientFlag=1;
	ResponceServerFlag=1;
	
	cout << "Closing stream of Request Client\n";
	pthread_join(idRequestClient, (void**) &ExitRequestClient);
	cout << "Closing stream of Responce Server\n";	
	pthread_join(idResponceServer, (void**) &ExitResponceServer);
	
	cout << "\n\n ExitRequestClient = " << ExitRequestClient << endl;
	cout << " ExitResponceServer = " << ExitResponceServer << "\n\n";
	
	cout << "Closing Socket\n";
	close (Socket);//закрыть сокет 
	
	cout << "\nThe program has ended\n";
	return 0;
}

