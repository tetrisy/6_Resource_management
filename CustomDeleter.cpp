#include <WinSock2.h>
#include <memory>

struct SocketDeleter {
	void operator()(SOCKET* socket) const {
		if (socket != nullptr && *socket != INVALID_SOCKET) closesocket(*socket);
		delete socket;
	}
};

std::unique_ptr<SOCKET, SocketDeleter> ptr1(new SOCKET(INVALID_SOCKET));

void closeSocket(SOCKET* socket) {
	if (socket != nullptr && *socket != INVALID_SOCKET) closesocket(*socket);
	delete socket;
}

std::unique_ptr<SOCKET, decltype(&closeSocket)> ptr2(new SOCKET(INVALID_SOCKET), &closeSocket);

auto socketLambdaClose = [](SOCKET* socket) {
	if (socket != nullptr && *socket != INVALID_SOCKET) closesocket(*socket);
	delete socket;
};

std::unique_ptr<SOCKET, decltype(socketLambdaClose)> ptr3(new SOCKET(INVALID_SOCKET), socketLambdaClose);