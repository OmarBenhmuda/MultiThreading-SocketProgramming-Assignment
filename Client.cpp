#include "thread.h"
#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace Sync;

int main(void)
{
	std::string msg = "";
	// Welcome the user
	std::cout << "SE3313 Lab 3 Client" << std::endl;

	// Create on ur socket

	while (true)
	{
		Socket socket("127.0.0.1", 3000);

		//Collecting user input
		std::cout << "What would you like to send to the server?" << std::endl
				  << std::endl;
		std::cin >> msg;
		socket.Open();

		std::cout << "Sending: " << msg << std::endl;

		//end the loop if the user types done

		ByteArray send(msg);
		socket.Write(send);

		if (msg == "done")
		{
			break;
		}

		ByteArray recieved;
		socket.Read(recieved);
		std::string newMsg = recieved.ToString();

		std::cout << "Recieved: " + newMsg << std::endl
				  << std::endl;

		socket.Close();
	}

	return 0;
}