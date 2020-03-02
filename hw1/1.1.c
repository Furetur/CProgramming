#include <stdio.h>


int main()
{
    int input = 0;
    printf("Enter the x:\n");
    scanf("%d",&input);
    const int inputSquared = input * input;
    const int result = 1 + (input + inputSquared) * (1 + inputSquared);
    printf("Result: %d", result);
    return 0;
}