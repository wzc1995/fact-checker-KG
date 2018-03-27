#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

double calc_similarity(const char* given, const char* candidate) {
    int n = strlen(given);
    int m = strlen(candidate);
    int i, j, ret;

    int **f = (int**)malloc((n + 1) * sizeof(int*));
    for (i = 0; i <= n; i++)
        f[i] = (int*)malloc((m + 1) * sizeof(int));

    
    for (i = 0; i <= n; i++)
        f[i][0] = i;
    for (j = 0; j <= m; j++)
        f[0][j] = j;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            if (given[i] == candidate[j])
                f[i + 1][j + 1] = f[i][j];
            else
                f[i + 1][j + 1] = min(f[i + 1][j], min(f[i][j + 1], f[i][j])) + 1;
        }
    
    ret = f[n][m];
    for (i = 0; i <= n; i++)
        free(f[i]);
    free(f);
    return 1 - 1.0 * ret / max(n, m);
}

char* find(const char* given, const char* file_path) {
    
    FILE *fp = fopen(file_path, "r"); 
    char *tmp = (char*)malloc(2000 * sizeof(char));
    int i, j, l;
    double res = 0;
    char *ans = (char *)malloc(2000 * sizeof(char));
    while (~fscanf(fp, "%s", tmp)) {
        l = strlen(tmp);
        char *candidate = (char*)malloc((l + 1) * sizeof(char));
        for (i = l - 1; i >= 0; i--)
            if (tmp[i] == '/') {
                for (j = i + 1; j < l - 1; j++) {
                    if (tmp[j] == '_')
                        tmp[j] = ' ';
                    candidate[j - i - 1] = tmp[j];
                }
                candidate[j - i - 1] = 0;
                break;
            }
        double cur = calc_similarity(given, candidate);
        if (res < cur) {
            res = cur;
            strcpy(ans, candidate);
        }
        free(candidate);
    }
    
    free(tmp);
    fclose(fp);
    return ans;
}

/*
int main() {
    printf("%.2lf\n", find_max_similarity("1134 Keplor"));
    return 0;
}
*/
