#include <stdio.h>
#include <stdlib.h>
#include "../lib/common.h"

int main()
{
    int n = 140, m = 140;
    char** input = get_str_mat_input("input", n, m + 1);
    int directions[8][2] = {
        // dx, dy
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1},
    };

    const char word[] = "XMAS";
    int valid = 0;
    for (int x = 0; x < m; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (input[x][y] != word[0]) 
                continue;
            
            for (int i = 0; i < 8; i++)
            {
                int xe = x + directions[i][0] * (sizeof(word) - 2);
                int ye = y + directions[i][1] * (sizeof(word) - 2);
                if (xe < 0 || xe >= m || ye < 0 || ye >= n)
                    continue;

                for (int offset = 1; offset < sizeof(word) - 1; offset++)
                {
                    if (input[x + directions[i][0] * offset][y + directions[i][1] * offset] != word[offset])
                        break;

                    if (offset == sizeof(word) - 2)
                        valid++;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++)
        free(input[i]);

    free(input);

    printf("Solution: %d\n", valid);
}