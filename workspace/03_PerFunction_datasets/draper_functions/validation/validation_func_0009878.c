submatrix(int first_row, int last_row, int first_col,
   int last_col) const
{
   REPORT
   Tracer tr("submatrix");
   int a = first_row - 1; int b = last_row - first_row + 1;
   int c = first_col - 1; int d = last_col - first_col + 1;
   if (a<0 || b<0 || c<0 || d<0) Throw(SubMatrixDimensionException());

   return GetSubMatrix(this, a, b, c, d, false);
}
