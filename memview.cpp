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

    cout << "Pid:   ";
    cin >> pid;
    cout << "Addr:  ";
    cin >> s; addr = stoull(s,nullptr,16);
    cout << "Size:  ";
    cin >> size;

    string memname = "/proc/" + pid + "/mem";
    int fd = open(memname.c_str(), O_RDONLY);
    if(fd == -1)
    {
        cerr << "Sorry, error open memory. Try as root\n";
        return -2;
    }

    for(pid = "", s = string(size,' ');;this_thread::sleep_for(1s))
    {
        off_t res = lseek(fd, (off_t)addr, SEEK_SET);
        if(res == (off_t)-1)
        {
            cerr << "Sorry, error seek memory\n";
            return -3;
        }
        int readed = read(fd, s.data(), s.size());
        auto p = s.find('\n');
        if ( p != s.npos) s[p] = 0;

        if (pid != s)
        {
            pid = s;
            cout << "<" << s << ">\n";
        }
    }
}
