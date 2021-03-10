#include "myBigChars.h"
#include "myTerm.h"

int main()
{
    // Draw();
    bc_box(5, 20, 10, 20);
    bc_printbigchar(zero, 20, 10, white, black);
    bc_printbigchar(one, 20, 20, blue, black);
    bc_printbigchar(two, 20, 30, red, black);
    bc_printbigchar(three, 20, 40, lightblue, black);
    bc_printbigchar(four, 20, 50, pink, black);
    bc_printbigchar(five, 20, 60, green, black);
    bc_printbigchar(six, 20, 70, yellow, black);
    bc_printbigchar(seven, 20, 80, blue, black);
    bc_printbigchar(eight, 20, 90, red, black);
    bc_printbigchar(nine, 20, 100, white, black);
    bc_printbigchar(plus, 20, 110, pink, black);
    return 0;
}
