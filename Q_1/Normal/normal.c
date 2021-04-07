#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NMAX 10000000

double mean(double *values, int n) {
    int i;
    double s = 0;

    for (i = 0; i < n; i++) {
        s += values[i];
    }
    return s / n;
}

double stddev(double *values, int n) {
    int i;
    double average = mean(values, n);
    double s = 0;

    for (i = 0; i < n; i++) {
        s += (values[i] - average) * (values[i] - average);
    }
    return sqrt(s / (n - 1));
}

double *generate(int n, double miu, double sigma) {
    int i;
    int m = n + n % 2;
    double *values = (double *)calloc(m, sizeof(double));
    double average, deviation;

    if (values) {
        for (i = 0; i < m; i += 2) {
            double x, y, rsq, f;
            do {
                x = 2.0 * rand() / (double)RAND_MAX - 1.0;
                y = 2.0 * rand() / (double)RAND_MAX - 1.0;
                rsq = x * x + y * y;
            } while (rsq >= 1. || rsq == 0.);
            f = sqrt(-2.0 * log(rsq) / rsq);
            values[i] = miu + (sigma * x * f);
            values[i + 1] = miu + (sigma * y * f);
        }
    }
    return values;
}

int main(void) {
    double *seq, miu, sigma;
    long int n = 1000000, file_num = 10;
    char filename[30] = "NormalDst.txt";
    miu = 100.0;
    sigma = 10.0;
    seq = generate(n, miu, sigma);
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%ld\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%lf\n", seq[i]);
    }
    fclose(fp);
}
