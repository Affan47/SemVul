MatrixExpEigen(Matrix& Mexp, ColumnVector& V, Matrix& U, Matrix& Uinv,
   SimpleIntArray& Cplx, Real t)
{
   Tracer et("MatrixExpEigen ");
   int n = Mexp.nrows();
   if (n != Mexp.ncols()) Throw(Logic_error("Not square"));
   if (n != V.nrows()) Throw(Logic_error("Incompatible dimension"));
   if (n != U.nrows()) Throw(Logic_error("Incompatible dimension"));
   if (n != U.ncols()) Throw(Logic_error("Incompatible dimension"));
   if (n != Uinv.nrows()) Throw(Logic_error("Incompatible dimension"));
   if (n != Uinv.ncols()) Throw(Logic_error("Incompatible dimension"));
   if (n != Cplx.Size()) Throw(Logic_error("Incompatible dimension"));
   ColumnVector W1(n);

   MatrixExpEigen(
      C_sub2(Mexp),
      n,
      V.data(),
      C_sub2(U),
      C_sub2(Uinv),
      Cplx.Data(),
      t,
      W1.data() );
}
