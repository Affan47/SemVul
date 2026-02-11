element(int m, int n)
{
   REPORT
   int w = upper_val+lower_val+1; int i = lower_val+n-m;
   if (m<0 || m>= nrows_val || n<0 || n>= ncols_val || i<0 || i>=w)
      Throw(IndexException(m,n,*this,true));
   return store[w*m+i];
}
