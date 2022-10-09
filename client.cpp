#include <bits/stdc++.h>
#include <arpa/inet.h>
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

		client_fd = connect(TCP_fd, (struct sockaddr*)&addr, sizeof(addr));
		if(client_fd < 0) {
			cout << "connection failed.\n";
			exit(0);
		}
		// connect to server
		cout << "TCP connection cmopleted\n";

	}
	string readMes() {
		return "";
	}

	void sendMes(string str) {
		send(TCP_fd, str.c_str(), str.size(), 0);

	}
private:
	int TCP_fd, client_fd;
};

int main(int argc, char** argv) {

	if (argc < 3) {
		cout << "Please input the port and IP for client side !!\n";
		return 0;
	}
	PORT = atoi(argv[2]); // extract the port

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0) {
		cout << "\nInvalid address/ Address not supported\n";
		return 0;
	}
	// setup address
	
	TCP tcp;
	string str;
	while(cin >> str) {
		tcp.sendMes(str);
	}
}