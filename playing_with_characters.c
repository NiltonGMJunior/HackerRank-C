#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    char ch;
    char s[256];
    char sen[256];

    scanf("%c%*c", &ch);
    scanf("%s%*c", &s);
    scanf("%[^\n]%*c", &sen);

    printf("%c\n%s\n%s", ch, s, sen);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
