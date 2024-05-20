#include "types.h"
#include "user.h"
#include "hdc.h"

int main(int argc, char* argv[])
{
    setvideomode(0x13);

    int hdc = beginpaint(0);
    setpencolour(16, 0, 0, 63);
    for(int i = 20; i <= 160; i += 20)
    {
        selectpen(hdc, 16);
        moveto(hdc, i, i + 20);
        lineto(hdc, i, i + 40);
        lineto(hdc, i + 20, i + 40);
        lineto(hdc, i + 20, i + 20);
        lineto(hdc, i, i + 20);
    }
    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}