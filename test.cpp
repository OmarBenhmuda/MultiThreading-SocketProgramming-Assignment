#include <string>
#include <iostream>

using namespace std;

int main(void)
{
    string msg = "hello";
    for (int i = 0; i < msg.length(); i++)
    {
        msg[i] = toupper(msg[i]);
    }

    cout << msg;

    return 0;
}