#include <stdio.h>

int NO_OF_LINES = 10e6;
const int MAX_VALUE = 200;

int main()
{
    FILE *fin = fopen("./UniformDst.txt", "r");

    FILE *fout = fopen("./normalized_uniform_distribution.txt", "w");

    int temp;
    long long i = 0;

    fscanf(fin, "%d\n", &temp);
    NO_OF_LINES = temp;

    fprintf(fout, "%d\n", NO_OF_LINES);
    while (!feof(fin))
    {
        i++;
        fscanf(fin, "%d\n", &temp);
        fprintf(fout, "%0.2f\n", ((float)temp) / MAX_VALUE);
        printf("\r%f %% done", ((float)i) / NO_OF_LINES * 100);
    }
    printf("\n");

    fclose(fin);
    fclose(fout);
    return 0;
}