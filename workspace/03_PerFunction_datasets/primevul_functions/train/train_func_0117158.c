DifSubK( int d0 , short *a4 , short *a5 )
{


        *a4++   =  0;
        d0 >>= 1;
        *a4     += d0;
        d0 >>= 1;
        *(a5-1) += d0;
        d0 >>= 1;
        *a5++   += d0;
        *a5     += d0;
}
