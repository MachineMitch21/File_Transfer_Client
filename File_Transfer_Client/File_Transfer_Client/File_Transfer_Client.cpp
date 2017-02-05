// File_Transfer_Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client_Socket.h"
#include "File_Utils.h"
#include <thread>
#include <iostream>
#include <string>
#include "Window.h"
#include <GL\glew.h>

int main()
{
	Client_Socket c_Socket("192.168.1.8", "4000");
	Window window("-_- **FILE_MANIA_CLIENT** -_-", 800, 600);
	
	glClearColor(1.0, 0.0, 0.0, .5);

	int iResult = 0;

	while(c_Socket.isConnected()) {

			if (!window.isClosed()) {
				window.clear();

				if (window.isKeyPressed(GLFW_KEY_S)) {
					c_Socket.send_file("Test.txt");
					glBegin(GL_TRIANGLES);

					glColor3f(0.0f, 1.0f, .5f);
					glVertex2f(0.0f, 0.5f);
					glVertex2f(-0.5f, -0.5f);
					glVertex2f(0.5f, -0.5f);

					glEnd();

					if (c_Socket.recv_data() > 0) {
						std::cout << "Bytes Received: " << std::endl;
					}
					else {
						std::cout << "Nothing received.." << std::endl;
					}
				}

				window.update();
			}

	}//end of if

    return 0;
}

