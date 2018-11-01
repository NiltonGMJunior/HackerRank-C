#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.
    for (int i = 0; i <= n * 2 - 2; i++ ) {
        for (int j = 0; j <= n * 2 - 2; j++) {
            int min_dist = i < j ? i : j;
            min_dist = min_dist < (n * 2 - 2 - i) ? min_dist : n * 2 - 2 - i;
            min_dist = min_dist < (n * 2 - 2 - j) ? min_dist : n * 2 - 2 - j;
            printf("%d ", n - min_dist);
        }
        printf("\n");
    }
    return 0;
}
