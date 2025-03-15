void merge_sort(int* arr, int start, int end);
int* get_ints_from_file(const char* filename, int* n);
char* get_str_input(const char* filename, int* n);
char** get_str_mat_input(const char* filename, int* n, int* m);
struct int_list* get_int_mat_from_file(const char* filename, int* n);
int binary_search(int* arr, int start, int end, int search_val);
void print_arr(int* arr, int n);

struct int_list
{
    int* values;
    int count;
};