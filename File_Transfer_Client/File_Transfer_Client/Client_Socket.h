#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include "File_Utils.h"

#pragma comment(lib, "Ws2_32.lib")



class Client_Socket
{
private:

	WORD mVersionRequested;
	WSADATA wsaData;
	int err;
	int iResult;
	SOCKET ConnectSocket = INVALID_SOCKET;
	char* PORT;
	File_Utils f_utils;
	bool socket_connected = false;
	addrinfo
		*result = NULL,
		*ptr = NULL,
		hints;

private:
	void initWinsock();
	void prep_socket();
	void resolve_addr(const char* serv_addr, const char* _port);
	void create_socket();
	void connect_socket();

public:
	bool isConnected();
	void sign_off();
	void send_file(const char* file_name);
	int recv_data();

public:
	Client_Socket(const char* serv_addr, const char* _port);
	~Client_Socket();
};

