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

        
    printf("Total difference: %d\n", diff);

    
    long similarity = 0;
    int* similarities = malloc(sizeof(int) * n1);
    for (int i = 0; i < n1; i++)
    {
        if (i > 0 && l1[i] == l1[i-1])
        {
            similarities[i] = similarities[i-1];
        }
        else
        {
            int search_idx = binary_search(l2, 0, n2 - 1, l1[i]);
            int count = 0;
            if (search_idx > -1)
            {
                while (search_idx < n2 && l2[search_idx++] == l1[i])
                    count++;
            }

            similarities[i] = l1[i] * count;
        }

        similarity += similarities[i];
    }

    printf("Similarity: %ld\n", similarity);
    free(l1);
    free(l2);
    free(similarities);
}