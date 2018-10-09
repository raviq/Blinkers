#ifndef GCT_H
#define GCT_H


class GCT
{

    double T2, *h;


public:
    GCT();

    void redun(double *x, double *y, int N, int m, int mmax, double epsilon);
    void InsertionSort(double *X, int *S, int M);
    void uniform (double *X, int M);
    void normalise(double *x, int N);
    int test();


};

#endif // GCT_H
