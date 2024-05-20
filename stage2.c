#include "types.h"
#include "user.h"
#include "hdc.h"

int main(int argc, char *argv[]) {
    setvideomode(0x13);
    int hdc = beginpaint(0);

    setpencolour(16, 63, 63, 63);
    setpencolour(17, 63, 01, 01);
    setpencolour(18, 01, 63, 01); 
    setpencolour(19, 01, 01, 63); 
    selectpen(hdc, 16);

    moveto(0, 100, 50);
    lineto(0, 200, 50);
    selectpen(hdc, 17);
    lineto(0, 200, 100);
    selectpen(hdc, 18);
    lineto(0, 100, 100);
    selectpen(hdc, 19);
    lineto(0, 100, 50);

    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}