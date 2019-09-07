#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char *a, const char *b)
{
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char *a, const char *b)
{
    return strcmp(b, a);
}

int count_distinct_characters(const char *a)
{
    int count = 0;
    while (*a != '\0')
    {
        if (!strchr(a + 1, *a))
            count++;
        a++;
    }
    return count;
}

int sort_by_number_of_distinct_characters(const char *a, const char *b)
{
    int diff = count_distinct_characters(a) - count_distinct_characters(b);
    return diff ? diff : lexicographic_sort(a, b);
}

int get_string_length(const char *a)
{
    if (*a == '\0')
        return 0;
    return 1 + get_string_length(a + 1);
}

int sort_by_length(const char *a, const char *b)
{
    int length_a = get_string_length(a);
    int length_b = get_string_length(b);
    if (length_a < length_b)
        return 1;
    if (length_a > length_b)
        return 0;
    return lexicographic_sort(a, b);
}

void swap_strings(char *a, char *b)
{
    char *temp = a;
    a = b;
    b = temp;
}

void string_sort(char **arr, const int len, int (*cmp_func)(const char *a, const char *b))
{
    qsort(arr, len, sizeof(char*), *cmp_func);
}

int main()
{
    int n;
    scanf("%d", &n);

    char **arr;
    arr = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    string_sort(arr, n, lexicographic_sort);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}