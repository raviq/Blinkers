// T test statistics for Granger causality Test


#include "gct.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b)	a>b?a:b


GCT::GCT()
{

}

//returns T2 statistics

void GCT::redun(double *x, double *y, int N, int m, int mmax, double epsilon)
{

  int i, j, s;
  int IYij, IXYij, IYZij, IXYZij;
  double disx, disy, disz, *Cy, *Cxy, *Cyz, *Cxyz, mu;

  mu = pow( 2.0*epsilon, m+2*mmax+1 );

  Cy = (double *) malloc(N*sizeof(double));
  Cxy = (double *) malloc(N*sizeof(double));
  Cyz = (double *) malloc(N*sizeof(double));
  Cxyz = (double *) malloc(N*sizeof(double));


  for (i=0;i!=N;i++)
  {
    h[i] = Cy[i] = Cxy[i] = Cyz[i] = Cxyz[i] = 0.0;
  }

  T2 = 0.0;

  for ( i = mmax ; i!=N ; i++ )
  {
    Cy[i]=Cxy[i]=Cyz[i]=Cxyz[i]=0.0;

    for (j=mmax;j!=N;j++)
    if (j!=i)
    {
      disx = disy = 0.0;
      for (s=1;s!=m+1;s++)
        disx = max(fabs(x[i-s]-x[j-s]),disx);

      for (s=1;s!=mmax+1;s++)
        disy = max(fabs(y[i-s]-y[j-s]),disy);

      if (disy <= epsilon)
      {
        Cy[i]++;

        if (disx <= epsilon)
        {
          Cxy[i]++;
        }

        disz = max(fabs(y[i]-y[j]),disy);
        if (disz <= epsilon)
        {
          Cyz[i]++;
          if (disx <= epsilon)
          {
            Cxyz[i]++;
          }
        }
      }   // end condition |Yi - Yj| < epsilon
    }   // end loop over j

    Cy[i] /= (double)(N-mmax);
    Cxy[i] /= (double)(N-mmax);
    Cyz[i] /= (double)(N-mmax);
    Cxyz[i] /= (double)(N-mmax);

    h[i] += 2.0/(double) mu*(Cxyz[i]*Cy[i] - Cxy[i]*Cyz[i])/6.0;

  }

  for (i=mmax;i!=N;i++)
  {
    for (j=mmax;j!=N;j++)
    if (j!=i)
    {

      IYij = IXYij = IYZij = IXYZij = 0;
      disx = disy = 0.0;

      for (s=1;s!=m+1;s++)
        disx = max(fabs(x[i-s]-x[j-s]),disx);

      for (s=1;s!=mmax+1;s++)
        disy = max(fabs(y[i-s]-y[j-s]),disy);

      if (disy <= epsilon)
      {

        IYij=1;
        if (disx <= epsilon)
           IXYij = 1;

        disz = max(fabs(y[i]-y[j]),disy);
        if (disz <= epsilon)
        {
          IYZij = 1;
          if (disx <= epsilon)
            IXYZij = 1;
        }
      }   // end condition |Yi - Yj| < epsilon

      h[i] += 2.0/(double) mu*(Cxyz[j]*IYij + IXYZij*Cy[j] - Cxy[j]*IYZij - IXYij*Cyz[j])/(double)(6*(N-mmax));
    }   // end second loop over j
  } // end loop over i

  for (i=mmax;i!=N;i++)
    T2 += h[i];

  T2 /= (double)(N-mmax);
  for (i=mmax;i!=N;i++)
     h[i] -= T2;


  free (Cy);
  free (Cxy);
  free (Cxyz);
  free (Cyz);

}
//=========================================================================================================
void GCT::InsertionSort(double *X, int *S, int M)
{
    int i, *I, j, r;
    double R;

    I = (int*) malloc (M*sizeof(int));

    for (i=0;i<M;i++)
      I[i]=i;

    for (i=1; i<M; i++)
      {
        R = X[i];
        r = i;
    for (j=i-1; (j>=0) && (X[j]>R); j--)
        {
      X[j+1] = X[j];
          I[j+1] = I[j];
        }
    X[j+1] = R;
        I[j+1] = r;
      }
    for (i=0; i<M; i++)
      S[I[i]]=i;

}
//=========================================================================================================

void GCT::uniform (double *X, int M)
{
  int *I, i;

  I = (int*) malloc (M*sizeof(int));
  InsertionSort(X, I, M);

  for (i=0;i<M;i++)
    X[i] = (double) I[i]/M*3.464101615;        // to make unit variance

}
//=========================================================================================================

/* normalize the time series to unit std. dev. */

void GCT::normalise(double *x, int N)
{
  int i;
  double mean=0.0, var=0.0;

  for (i=0;i!=N;i++)
  {
    mean += x[i];
    var += x[i]*x[i];
  }

  mean /= (double)(N);
  var /= (double)(N);
  var -= mean*mean;

  for (i=0;i!=N;i++)
    x[i] = (x[i]-mean)/sqrt(var);

  return;
}
//=========================================================================================================
int GCT::test()
{
  char infil1name[] = "/Users/rhad0003/Desktop/Blinkers/qt/Blinker/in1.txt",
       infil2name[] = "/Users/rhad0003/Desktop/Blinkers/qt/Blinker/in2.txt";

  double epsilon = .5, // bandwidth
         VT2,  p_T2, *ohm, *cov, T2_TVAL, sigma[4][4];
  int i, k,
          m = 1, // embedding dimension
          K, N;

//=================================================================================
// importat: files must contain series of different length.

 // generated with gen.py
  double x[] = { 0.0, 0.10393548579969401, 0.2071480651030484, 0.4553798938858782, 0.736905179318202, 1.1741770541075387, 1.6343075814295456, 1.7881867899802553, 2.2596880173488745, 2.42488254996527 };
  double y[] = { 0.0, 0.10393548579969401, 0.2071480651030484, 0.4553798938858782, 0.736905179318202, 1.1741770541075387, 1.6343075814295456, 1.7881867899802553, 2.2596880173488745, 2.42488254996527 };
  //double y[] = { 0.0, 0.02, 0.12393548579969402, 0.22714806510304839, 0.4753798938858782, 0.756905179318202, 1.1941770541075387, 1.6543075814295456, 1.8081867899802553, 2.2796880173488745 };

  N = sizeof(x)/sizeof(double);
  h = (double *) malloc(N*sizeof(double));
  K = (int)(sqrt(sqrt(N)));
  ohm = (double *) malloc(K*sizeof(double));
  cov = (double *) malloc(K*sizeof(double));

  normalise(x, N);
  normalise(y, N);

  // redun(x,y, ..) test statistic for X -> Y
  redun(x, y, N, m, m, epsilon);

  ohm[0] = 1.0;
  for ( k = 1 ; k < K ; k++ )
  {
    ohm[k] = 2.0*(1.0-k/(double)(K));
  }

  // determine autocovariance of h[i]

  for ( k = 0 ; k != K ; k++ )
  {
    cov[k] = 0.0;
    for ( i = m+k ; i!=N ; i++ )
      cov[k] += h[i]*h[i-k];
    cov[k] /= (double)(N-m-k);
  }

  T2_TVAL = VT2 = 0.0;

 // variance of T2

  for (k=0;k!=K;k++)
    VT2 += 9.0 * ohm[k] * cov[k];

  T2_TVAL = T2 * sqrt(N-m) / sqrt(VT2);

  p_T2 = 0.5 - .5*erf(T2_TVAL/sqrt(2.0));

  printf("Series length=%d, embedding dimension=%d, bandwidth=%f\n", N, m, epsilon);
  printf("Null hypothesis: %s does not cause %s\n", infil1name, infil2name);
  printf("T statistics=%.3f, p-value=%1.5f\n", T2_TVAL, p_T2);
  printf("\n");

  redun(y, x, N, m, m, epsilon);

  ohm[0] = 1.0;

  for (k=1;k<K;k++)
    ohm[k] = 2.0*(1.0-k/(double)(K));

  // determine autocovariance of h[i]

  for (k=0;k!=K;k++)
  {
    cov[k] = 0.0;
    for (i=m+k;i!=N;i++)
      cov[k] += h[i]*h[i-k];
    cov[k] /= (double)(N-m-k);
  }

  T2_TVAL = VT2 = 0.0;

  // variance of T2

  for (k=0;k!=K;k++)
    VT2 += 9.0*ohm[k]*cov[k];

  T2_TVAL = T2*sqrt(N-m)/sqrt(VT2);

  p_T2 = 0.5 - .5*erf(T2_TVAL/sqrt(2.0));

  printf("Null hypothesis: %s does not cause %s\n", infil2name, infil1name);
  printf("T statistics=%.3f, p-value=%1.5f\n", T2_TVAL, p_T2);

 //-- TODO find write one
 // fcloseall();

  printf("\n");
  return 0;
}


