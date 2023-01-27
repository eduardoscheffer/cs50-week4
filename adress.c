#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n; // the pointer (*p) represents the location of the variable it is receiving (&n) in this case 50;
    printf("%p\n", p); // prints the location in memory of variable n;
    printf("%i\n", *p); // prints the variable stored in pointer p which is the variabel n = 50;
}