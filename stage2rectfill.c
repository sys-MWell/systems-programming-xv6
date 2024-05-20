#include "types.h"
#include "user.h"
#include "rect.h"
#include "hdc.h"

int main(int argc, char *argv[]) {
    setvideomode(0x13);
    int hdc = beginpaint(0);

    struct rect r = {10, 100, 50, 200};
    struct rect r1 = {50, 100, 90, 200};
    struct rect r2 = {90, 100, 130, 200};
    
    setpencolour(16, 63, 0, 0);
    setpencolour(17, 0, 63, 0);
    setpencolour(18, 0, 0, 63);
    
    selectpen(hdc, 16);
    fillrect(hdc, &r);

    selectpen(hdc, 17);
    fillrect(hdc, &r1);

    selectpen(hdc, 18);
    fillrect(hdc, &r2);

    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}