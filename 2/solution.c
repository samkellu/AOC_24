#include <stdio.h>
#include <stdlib.h>
#include "../lib/common.h"

int is_safe(struct int_list input, int skip_idx)
{

        int all_increasing = 1;
        int all_decreasing = 1;
        int all_difference = 1;
        int start = skip_idx == 0 || skip_idx == 1 ? 2 : 1;
        for (int j = start; j < input.count; j++)
        {
            if (j == skip_idx)
                continue;

            int cur = input.values[j];
            int prev = input.values[j-1 == skip_idx ? j-2 : j-1];
            if (cur > prev && all_decreasing)
                all_decreasing = 0;

            if (cur < prev && all_increasing)
                all_increasing = 0;

            int diff = cur > prev ? cur - prev : prev - cur;
            if (diff < 1 || diff > 3 )
                all_difference = 0;

            if (!all_difference || !(all_decreasing || all_increasing))
                break;
        }

    return all_difference && (all_decreasing || all_increasing);
} 

int main()
{
    int n;
    struct int_list* input = get_int_mat_from_file("input", &n);
    int num_safe = 0;
    for (int i = 0; i < n; i++)
    {
        if (is_safe(input[i], -1))
            num_safe++;
    }

    printf("Number of safe reports: %d\n", num_safe);

    num_safe = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = -1; j < input[i].count; j++)
        {
            if (is_safe(input[i], j))
            {
                num_safe++;
                break;
            }
        }
    }

    printf("Number of safe reports with problem dampener: %d\n", num_safe);

    for (int i = 0; i < n; i++)
        free(input[i].values);

    free(input);
}