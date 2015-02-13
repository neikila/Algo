#include <stdio.h>
#include "time.h"

int main()
{
    srand(time(NULL));
    int count = 10;
    int temp = count;
    while ( temp-- )
        printf("%d\n", rand()%count);
    return 0;
}
