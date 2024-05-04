#include <unistd.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <cstring>

using namespace std;

// String to change and read
char str[64] = "Now is ";

int main()
{
    // Output mem info 
    cout <<
        "PID:    " << getpid()    << "\n" <<
        "ADDR:   " << (void*)str  << "\n" <<
        "SIZE:   " << sizeof(str) << "\n";
    cout << "You are welcome!\n";

    // Change string every 1s afres 20s delay
    for(this_thread::sleep_for(20s);;this_thread::sleep_for(1s))
    {
        time_t now = time(0);
        strcpy(str + 7,asctime(gmtime(&now)));
        cout << strlen(str) << "  " << str;
    }
}
