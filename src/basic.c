#include "rpn.h"
#include "stek.h"
#include <string.h>

int main()
{
    char* str = malloc(sizeof(char) * 10);
    strcpy(str, "(1+2)*(4/2)");
    char* out = malloc(sizeof(char) * 10);
    translate_to_rpn(str, out);
    printf("%s\n", out);
    return 0;
}
