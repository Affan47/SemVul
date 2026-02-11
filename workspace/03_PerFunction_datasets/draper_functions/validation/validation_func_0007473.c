matrix_diag_XXt_yyt_float (const float* X,size_t p,const float* y,size_t n,float *res)
{
    size_t i,j;
    double m1 = 0, m2, sum;
    for (i=0;i<n;i++){
        m1 += y[i];
        res[i]=0;
    }
    m1 /= n;
    for (j=0;j<p;j++) {
        m2=0;
        for (i=0;i<n;i++)
            m2 += X[i+j*n];
        m2 /=n;
        sum=0;
        for (i=0;i<n;i++)
            sum+=(y[i]-m1)*(X[i+j*n]-m2);
        for (i=0;i<n;i++)
            res[i]+=X[i+j*n]*sum;
    }

    for (i=0;i<n;i++) {
        res[i]*=(y[i]-m1);
    }
}
