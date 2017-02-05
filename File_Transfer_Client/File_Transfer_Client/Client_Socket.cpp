#include "Client_Socket.h"



Client_Socket::Client_Socket(const char* serv_addr, const char* _port)
{
	initWinsock();
	prep_socket();
	resolve_addr(serv_addr, _port);
	create_socket();
	connect_socket();
}

void Client_Socket::initWinsock() {

	//Get winsock version 2.2
	mVersionRequested = MAKEWORD(2, 2);								
	err = WSAStartup(mVersionRequested, &wsaData);

	if (err != 0) {
		std::cout << "WSAStartup failed with error: " << err << std::endl;
	}
	else {
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
			std::cout << "Could not find a usable version of Winsock.dll!" << std::endl;
			WSACleanup();
		}
		else {
			std::cout << "Winsock 2.2 dll was located!" << std::endl;
		}
	}

}

void Client_Socket::prep_socket() {

	//Clear memory and setup socket type and protocol
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void Client_Socket::resolve_addr(const char* serv_addr, const char* _port) {
	//Check address validity
	iResult = getaddrinfo(serv_addr, _port, &hints, &result);
	if (iResult != 0) {
		std::cout << "Address Info failure: " << iResult << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "--Address at " << serv_addr << " resolved--" << std::endl;
		ptr = result;
	}
}

void Client_Socket::create_socket() {
	
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Socket Error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
	}
	else {
		std::cout << "Socket Created!!" << std::endl;
	}
}

void Client_Socket::connect_socket() {
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}
	else {
		std::cout << "Connection ESTABLISHED!!!!" << std::endl;
		socket_connected = true;
	}
	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Unable to connect to server!" << std::endl;
		WSACleanup();
		socket_connected = false;
	}
}

void Client_Socket::sign_off() {
		closesocket(ConnectSocket);
		WSACleanup();
}

bool Client_Socket::isConnected() {
	return socket_connected;
}

void Client_Socket::send_file(const char* file_name) {

	//Get data from file and store in a buffer for send()
	const char* sendbuf = f_utils.read_file(file_name);
	int result = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);

	if (result != SOCKET_ERROR) {
		std::cout << "Transfer successful: " << result << std::endl;
	}
	else {
		std::cout << "Transfer failed: " << result << std::endl;
		//closesocket(ConnectSocket);
		//WSACleanup();
	}

}

int Client_Socket::recv_data() {
	char recvbuf[1024];

	iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);
	
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	return iResult;
}


Client_Socket::~Client_Socket()
{
}
