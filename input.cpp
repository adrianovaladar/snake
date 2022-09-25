#include<bits/stdc++.h>
#include <chrono>
#include <termios.h>

/* http://www.flipcode.com/archives/_kbhit_for_Linux.shtml */
int morePortable() {
    struct timeval timeout;
    fd_set rdset;

    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    return select(STDOUT_FILENO, &rdset, NULL, NULL, &timeout);
}

int _kbhit(void) {
    static int initialized = 0;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

#if 0
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting;
#else
    return morePortable();
#endif
}