#include <chrono>
#include <thread>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc,char **argv) {
    int status = 0;   
    pid_t pid = fork();
    switch(pid){
    case -1:
        perror("fork");
        break;
    case 0: 
        execv("OC_Lab_3_Child", argv);
        perror("Error...EXEC\n");
    default:
    	cout << "ID of Child procces:" << pid << endl;
    	cout << "ID of This procces:" << getpid() << endl;
    	cout << "ID of Parent procces:" << getppid() << endl;
        while (waitpid (pid, &status, WNOHANG) == 0) {
        	cout << "waiting for...\n";
            	std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        cout << "\n\nexitchild = " << status << endl;
    }
    return 0;
}
