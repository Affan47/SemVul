QRZT(const Matrix& X, Matrix& Y, Matrix& M)
{
   REPORT
   Tracer et("QRZT(2)");
   int n = X.Ncols(); int s = X.Nrows(); int t = Y.Nrows();
   if (Y.Ncols() != n)
      { Throw(ProgramException("Unequal row lengths",X,Y)); }
   M.resize(t,s);
   Real* xi = X.Store(); int k;
   for (int i=0; i<s; i++)
   {
      Real* xj0 = Y.Store(); Real* xi0 = xi;
      for (int j=0; j<t; j++)
      {
         Real sum=0.0;
         xi=xi0; Real* xj=xj0; k=n; while(k--) { sum += *xi++ * *xj++; }
         xi=xi0; k=n; while(k--) { *xj0++ -= sum * *xi++; }
         M.element(j,i) = sum;
      }
   }
}
