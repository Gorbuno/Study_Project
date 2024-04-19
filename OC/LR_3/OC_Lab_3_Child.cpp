
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char * argv[]) {
	switch (argc){
    	case 1:
   		 printf("В командной строке необходимо ввести число,с которого начинается отсчет. \n Попробуйте снова.\n");
    		exit(1);
  
	default:
  		for (int i=1;i<argc;i++){
  		 cout << endl << argv[i]<< endl<<endl;
  		 sleep(1);
  		 }
  } 
	cout << "ID of Parents procces:"<< getppid() << endl;
	cout << "ID of Child procces:"<< getpid() << endl << endl;
    	exit(0);
}

