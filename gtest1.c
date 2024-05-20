#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    setvideomode(0x13);
    //setpixel(0, 100, 50);
    
    moveto(0, 100, 50);
    lineto(0, 200, 50);
    lineto(0, 200, 100);
    lineto(0, 100, 100);
    lineto(0, 100, 50);
    lineto(0, 200, 100);

    getch();
    setvideomode(0x03);
    exit();
}