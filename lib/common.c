#include <stdio.h>
#include <stdlib.h>

void merge_sort(int* arr, int start, int end)
{
    if (start >= end)
        return;
    
    int mid = start + (end - start) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);

    int l_n = mid - start + 1;
    int r_n = end - mid;
    
    int* l_arr = malloc(sizeof(int) * l_n);
    int* r_arr = malloc(sizeof(int) * r_n);
    if (!l_arr || !r_arr)
    {
        free(l_arr);
        free(r_arr);
        return;
    }
    
    for (int q = 0; q < l_n; q++)
        l_arr[q] = arr[q + start];
    
    for (int q = 0; q < r_n; q++)
        r_arr[q] = arr[q + 1 + mid];
    
    int l_idx = 0;
    int r_idx = 0;
    while (l_idx < l_n && r_idx < r_n)
    {
        if (l_arr[l_idx] <= r_arr[r_idx])
        {
            arr[start++] = l_arr[l_idx++];
        }
        else
        {
            arr[start++] = r_arr[r_idx++];
        }
    }

    while (l_idx < l_n)
        arr[start++] = l_arr[l_idx++];

    while (r_idx < r_n)
        arr[start++] = r_arr[r_idx++];

    free(l_arr);
    free(r_arr);
}

int* get_ints_from_file(const char* filename, int* n)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    int* ints = malloc(0);
    int idx = 0;
    *n = 0;

    char buf[64];
    while (!feof(fp) && fgets(buf, 64, fp))
    {
        ints = realloc(ints, sizeof(int) * (idx + 1));
        ints[idx++] = atoi(buf);
    }

    fclose(fp);
    *n = idx;
    return ints;
}


void print_arr(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// int main()
// {
//     int arr[] = {
//         2, 7, 3, 2, 6, 8, 9, 12, 6, 4, 12, 22
//     };

//     int n = sizeof(arr) / sizeof(int);

//     printf("%d\n", n);
//     print_arr(arr, n);

//     merge_sort(arr, 0, n - 1);

//     print_arr(arr, n);

// }