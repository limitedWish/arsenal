#include <stdio.h>
#include "fibonacci.h"

int
main(int argc, char **argv)
{
    printf("fibonacci(%d) = %d\n", argc, fibonacci(argc));
    return 0;
}
