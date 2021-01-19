#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include "Semaphore.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace Sync;
Semaphore s("semaphore", 5, true);
// This thread handles the server operations
class ServerThread : public Thread
{
private:
    SocketServer &server;

public:
    ServerThread(SocketServer &server)
        : server(server)
    {
    }

    ~ServerThread()
    {
        server.Shutdown();
    }

    virtual long ThreadMain()
    {

        s.Wait();
        std::string msg = "asdasda";

        // Wait for a client socket connection
        Socket *connection = new Socket(server.Accept());
        Socket &sockRef = *connection;

        ByteArray data;
        sockRef.Read(data);
        msg = data.ToString();
        std::cout << "Recieved: " + msg << std::endl;

        //Turn msg to all caps
        for (int i = 0; i < msg.length(); i++)
        {
            msg[i] = toupper(msg[i]);
        }

        if (msg == "DONE")
        {
            server.Shutdown();
            exit(0);
        }

        //outputs msg in server
        std::cout << "Sending: " + msg << std::endl
                  << std::endl;

        ByteArray newData(msg);
        // Send it back
        sockRef.Write(newData);

        s.Signal();

        return 1;
    }
};

int main(void)
{
    std::cout << "I am a server." << std::endl;

    // Create our server
    SocketServer server(3000);
    while (true)
    {
        s.Wait();
        new ServerThread(server);
        s.Signal();
    }
}