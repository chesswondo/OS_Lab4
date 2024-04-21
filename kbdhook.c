#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

// Device name:
const char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

int main()
{
    int fd = open(device, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Cannot open %s: error %s.\n", device, strerror(errno));
        return EXIT_FAILURE;
    }

    for(;;)
    {

        struct input_event kbd_event;  // Kbd event
        ssize_t n = read(fd, &kbd_event, sizeof(kbd_event));
        if (n == (ssize_t)-1)
        {
            if (errno == EINTR) continue;
            break;
        }
        else if (n != sizeof(kbd_event))
        {
            errno = EIO;
            break;
        }

        if (kbd_event.type == EV_KEY &&
            kbd_event.value >= 0 &&
            kbd_event.value <= 2)
        {
            const char *acts[3] = {
                "RELEASE",
                "PRESS  ",
                "REPEAT "
            };
            printf("%s code 0x%04x (%d)\n",
                   acts[kbd_event.value], (int)kbd_event.code,
                   (int)kbd_event.code);
        }
    }
    fflush(stdout);
    fprintf(stderr, "%s\n", strerror(errno));
    return EXIT_FAILURE;
}
