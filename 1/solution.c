#include <stdio.h>
#include <stdlib.h>
#include "../lib/common.h"

int main()
{
    int n1, n2;
    int* l1 = get_ints_from_file("input1", &n1);
    int* l2 = get_ints_from_file("input2", &n2);

    merge_sort(l1, 0, n1 - 1);
    merge_sort(l2, 0, n2 - 1);

    int diff = 0;
    for (int i = 0; i < n1; i++)
        diff += l1[i] > l2[i] ? l1[i] - l2[i] : l2[i] - l1[i];

    free(l1);
    free(l2);

    printf("Total difference: %d\n", diff);
}