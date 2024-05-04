#include <iostream>
#include <string>
#include <thread>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    string pid, s;
    unsigned long long addr, size;
    // Get info about memory
    cout << "Pid:   ";
    cin >> pid;
    cout << "Addr:  ";
    cin >> s; addr = stoull(s,nullptr,16);
    cout << "Size:  ";
    cin >> size;

    // device name
    string memname = "/proc/" + pid + "/mem";
    int fd = open(memname.c_str(), O_RDONLY);
    if(fd == -1)
    {
        cerr << "Sorry, error open memory. Try as root\n";
        return -2;
    }
    // Every 1s read mem and output (if it changes)
    for(pid = "", s = string(size,' ');;this_thread::sleep_for(1s))
    {
        // Seek to required position
        off_t res = lseek(fd, (off_t)addr, SEEK_SET);
        if(res == (off_t)-1)
        {
            cerr << "Sorry, error seek memory\n";
            return -3;
        }
        // read chunk
        int readed = read(fd, s.data(), s.size());
        // Limit string
        auto p = s.find('\n');
        if ( p != s.npos) s[p] = 0;

        // Output if different
        if (pid != s)
        {
            pid = s;
            cout << "<" << s << ">\n";
        }
    }
}
