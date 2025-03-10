#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

int is_valid_int(char* input, int* out)
{
    int sign = 1;
    int offset = 0;
    if (*input == '-')
    {
        offset++;
        sign *= -1;
    }
    
    *out = 0;
    int len = 0;
    while (*(input + offset) >= '0' && *(input + offset) <= '9' && len <= 3)
    {
        *out *= 10;
        *out += *(input + offset) - '0';
        offset++;
        len++;
    }

    if (len > 3)
        return -1;

    *out *= sign;
    return offset;
}

int is_match(char* input, char* comp)
{
    char* do_inst = "do()";
    if (strlen(input) < strlen(comp))
        return 0;

    for (int i = 0; i < strlen(comp); i++)
    {
        if (input[i] != comp[i])
            return 0;
    }

    return 1;
}

long long int get_output(char* input, int n, int part2)
{
    int enabled = 1;
    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        int offset = i;
        if (part2 && is_match(input + offset, "do()"))
        {
            offset += 4;
            enabled = 1;
        }
        else if (part2 && !enabled) continue;
        else if (part2 && is_match(input + offset, "don't()"))
        {
            offset += 7;
            enabled = 0;
        }
        else if (is_match(input + offset, "mul("))
        {
            offset += 4;
        }
        else continue;

        int x;
        int res_offset = is_valid_int(input + offset, &x);
        if (!res_offset)
            continue;

        offset += res_offset;
        if (*(input + offset++) != ',')
            continue;

        int y;
        res_offset = is_valid_int(input + offset, &y);
        if (!res_offset)
            continue;

        offset += res_offset;
        if (*(input + offset) != ')')
            continue;

        res += x * y;
    }

    return res;
}

int main()
{
    int n;
    char* input = get_str_input("input", &n);
    
    printf("Result of uncorrupted instructions: %lld\n", get_output(input, n, 0));
    printf("Result of uncorrupted instructions (part 2): %lld\n", get_output(input, n, 1));
}