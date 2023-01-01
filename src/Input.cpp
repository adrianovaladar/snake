#include "Input.h"
#include <sys/ioctl.h>
#include <termios.h>

// https://stackoverflow.com/questions/29335758/using-kbhit-and-getch-on-linux

void Input::enableRawMode() {
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);// Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void Input::disableRawMode() {
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool Input::kbHit() {
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}