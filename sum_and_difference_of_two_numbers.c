#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int int1, int2;
    float float1, float2;

    scanf("%d %d%*c", &int1, &int2);
    scanf("%f %f%*c", &float1, &float2);

    printf("%d %d\n%.1f %.1f\n", int1 + int2, int1 - int2, float1 + float2, float1 - float2);

    return 0;
}
