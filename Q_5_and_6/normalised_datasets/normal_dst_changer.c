#include <stdio.h>
#include <limits.h>

int NO_OF_LINES = 10e6;
double MAX_VALUE = INT_MIN * 1.0;

void findMax(int n)
{

    FILE *fin = fopen("./NormalDst.txt", "r");

    double temp = 0;
    int tmp2;
    fscanf(fin, "%d\n", &tmp2);
    for (int i = 0; i < n; i++)
    {

        fscanf(fin, "%lf\n", &temp);
        if (temp > MAX_VALUE)
        {
            MAX_VALUE = temp;
        }
    }

    fclose(fin);
}

int main()
{
    FILE *fin = fopen("./NormalDst.txt", "r");

    FILE *fout = fopen("./normalized_normal_distribution.txt", "w");

    double temp;
    int tmp2;
    long long i = 0;

    fscanf(fin, "%d\n", &tmp2);
    NO_OF_LINES = tmp2;
    findMax(NO_OF_LINES);

    fprintf(fout, "%d\n", NO_OF_LINES);
    while (!feof(fin))
    {
        i++;
        fscanf(fin, "%lf\n", &temp);
        fprintf(fout, "%0.4f\n", ((float)temp) / MAX_VALUE);
        printf("\r%f %% done", ((float)i) / NO_OF_LINES * 100);
    }
    printf("\nMAX VALUE= %lf\n", MAX_VALUE);

    fclose(fin);
    fclose(fout);
    return 0;
}