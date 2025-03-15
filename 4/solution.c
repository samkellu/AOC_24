#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

int main()
{
    int n, m;
    char** input = get_str_mat_input("input", &n, &m);
    
    printf("%d %d\n", n, m);
    fflush(stdout);
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
            printf("%d %d %d\r", valid, x, y);
            fflush(stdout);
            if (input[x][y] != word[0]) 
                continue;

            for (int i = 0; i < 8; i++)
            {
                int xe = x + directions[i][0] * sizeof(word);
                int ye = y + directions[i][1] * sizeof(word);
                if (xe < 0 || xe >= n || ye < 0 || ye >= m)
                    continue;

                for (int offset = 1; offset < sizeof(word); offset++)
                {
                    if (input[x + directions[i][0] * offset][y + directions[i][1] * offset] != word[offset])
                        break;

                    if (offset == sizeof(word) - 1)
                    {
                        valid++;
                    }
                }
            }
        }

        free(input[x]);
    }

    free(input);

    printf("Solution: %d\n", valid);
}