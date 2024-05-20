#include "types.h"
#include "user.h"
#include "hdc.h"

int main(int argc, char *argv[]) {
    setvideomode(0x13);

    int hdc = beginpaint(0);

    selectpen(hdc, 15);
    moveto(hdc, 100, 50);
    lineto(hdc, 200, 50);
    lineto(hdc, 200, 100);
    lineto(hdc, 100, 100);
    lineto(hdc, 100, 50);

    endpaint(hdc);

    getch();
    setvideomode(0x03);
    exit();
}