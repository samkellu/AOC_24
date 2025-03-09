#include <stdio.h>
#include <stdlib.h>
#include "../lib/common.h"

int get_num_safe(struct int_list* input, int n, int skip_per_row)
{
    int num_safe = 0;
    for (int i = 0; i < n; i++)
    {
        int all_increasing = 1;
        int all_decreasing = 1;
        int all_difference = 1;
        int skips_left = skip_per_row;
        for (int j = 1; j < input[i].count; j++)
        {
            int cur = input[i].values[j];
            int prev = input[i].values[j-1];
            if (cur > prev && all_decreasing)
            {
                if (skips_left)
                {
                    skips_left--;
                    continue;
                }

                all_decreasing = 0;
            }

            if (cur < prev && all_increasing)
            {
                if (skips_left)
                {
                    skips_left--;
                    continue;
                }

                all_increasing = 0;
            }

            int diff = cur > prev ? cur - prev : prev - cur;
            if (diff < 1 || diff > 3 )
            {
                if (skips_left)
                {
                    skips_left--;
                    continue;
                }
                
                all_difference = 0;
            }

            if (!all_difference || !(all_decreasing || all_increasing))
                break;
        }

        if (all_difference && (all_decreasing || all_increasing))
            num_safe++;
    }

    return num_safe;
} 

int main()
{
    int n;
    struct int_list* input = get_int_mat_from_file("input", &n);

    int num_safe = get_num_safe(input, n, 0);
    printf("Number of safe reports: %d\n", num_safe);

    num_safe = get_num_safe(input, n, 1);
    printf("Number of safe reports with problem dampener: %d\n", num_safe);

    for (int i = 0; i < n; i++)
        free(input[i].values);

    free(input);
}