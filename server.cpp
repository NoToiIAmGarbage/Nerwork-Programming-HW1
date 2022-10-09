#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int opt = 1, PORT;
const int mx_q = 100;
struct sockaddr_in addr;

char buffer[1024];

class TCP {
public:
	TCP() {
		TCP_fd = socket(AF_INET, SOCK_STREAM, 0);
		// file descriptor of TCP

		setsockopt(TCP_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		// set options

		bind(TCP_fd, (struct sockaddr*)&addr, sizeof(addr));
		// bind the fd to the address struct

		listen(TCP_fd, mx_q);
		// starts listening at PORT
		
		int addrlen = sizeof(addr);
		new_socket = accept(TCP_fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
		if(new_socket < 0) {
			cout << "Read fail\n";
		}

		// cout << "server TCP connection established\n";
	}
	string readMes() {
		read(new_socket, buffer, 1024);
		printf("%s\n", buffer);
		return "";
	}

	void sendMes(string str) {

	}
private:
	int TCP_fd, new_socket;
};

int main(int argc, char** argv) {

	if (argc < 2) {
		cout << "Please input the port for server side !!\n";
		return 0;
	}
	PORT = atoi(argv[1]); // extract the port

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	// setup address
	
	TCP tcp;

	while(true) {
		tcp.readMes();
		// sleep(5);
	}
}