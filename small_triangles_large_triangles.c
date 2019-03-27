#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

/* This calculates the area of a triangle based on Heron's formula, given that any triangle is defined by the length of its sides
 */
double get_triangle_area(triangle* tr)
{
    double p = (tr->a + tr->b + tr->c) / 2.0;
    return sqrt(p * (p - tr->a) * (p - tr->b) * (p - tr->c));
}

/* This performs a selection sort of triangles based on their areas.
 * Smaler triangles come first.
 */
void sort_by_area(triangle* tr, int n) {
    for (int start_index = 0; start_index < n - 1; ++start_index)
    {
        int smallest_index = start_index;
        for (int current_index = start_index + 1; current_index < n; ++current_index)
        {
            if (get_triangle_area(tr + current_index) < get_triangle_area(tr + smallest_index))
            {
                smallest_index = current_index;
            }
        }
        triangle temp = tr[start_index];
        tr[start_index] = tr[smallest_index];
        tr[smallest_index] = temp;
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}