#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#pragma region sorting

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
    
    for (int q = 0; q < l_n; q++)
        l_arr[q] = arr[q + start];
    
    for (int q = 0; q < r_n; q++)
        r_arr[q] = arr[q + 1 + mid];
    
    int l_idx = 0;
    int r_idx = 0;
    while (l_idx < l_n && r_idx < r_n)
    {
        if (l_arr[l_idx] <= r_arr[r_idx])
            arr[start++] = l_arr[l_idx++];

        else
            arr[start++] = r_arr[r_idx++];
    }

    while (l_idx < l_n)
        arr[start++] = l_arr[l_idx++];

    while (r_idx < r_n)
        arr[start++] = r_arr[r_idx++];

    free(l_arr);
    free(r_arr);
}

#pragma endregion

#pragma region searching

int binary_search(int* arr, int start, int end, int search_val)
{
    if (start == end)
        return arr[start] == search_val ? start : -1;

    int mid = start + (end - start) / 2;
    if (arr[mid] < search_val)
        return binary_search(arr, mid + 1, end, search_val);
        
    return binary_search(arr, start, mid, search_val);
}

#pragma endregion

#pragma region input_handling

char* get_str_input(const char* filename, int* n)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    char* str = malloc(0);
    int offset = 0;

    char buf[256];
    while (!feof(fp))
    {
        int bytes = fread(buf, sizeof(char), 256, fp);
        str = realloc(str, sizeof(char) * (offset + bytes));
        memcpy(str + offset, buf, bytes);
        offset += bytes;
    }

    fclose(fp);
    *n = offset;
    return str;
}

char** get_str_mat_input(const char* filename, int n, int m)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    char** mat = malloc(n * sizeof(char*));
    int i = 0;
    while (!feof(fp))
    {
        char* str = malloc(m * sizeof(char));
        fread(str, sizeof(char), m, fp);
        mat[i++] = str;      
    }
    
    fclose(fp);
    return mat;
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

struct int_list* get_int_mat_from_file(const char* filename, int* n)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    struct int_list* lists = malloc(0);
    int idx = 0;
    *n = 0;

    char buf[256];
    while (!feof(fp) && fgets(buf, 256, fp))
    {
        struct int_list cur_ls = { values: malloc(0), count: 0 };
        char* token = strtok(buf, " ");
        while (token != NULL)
        {
            cur_ls.values = realloc(cur_ls.values, sizeof(int) * (cur_ls.count + 1));
            cur_ls.values[cur_ls.count++] = atoi(token);
            token = strtok(NULL, " ");
        }
        
        lists = realloc(lists, sizeof(struct int_list) * (idx + 1));
        lists[idx++] = cur_ls;
    }

    fclose(fp);
    *n = idx;
    return lists;
}

#pragma endregion

#pragma region display

void print_arr(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

#pragma endregion