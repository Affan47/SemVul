GetCol(MatrixColX& mrc)
{
   REPORT
   int col=mrc.rowcol; mrc.skip=col; mrc.length=nrows_val;
   int i=nrows_val-col; mrc.storage=i; mrc.data = mrc.store + col;

   if (+(mrc.cw*LoadOnEntry))
   {
      REPORT  Real* ColCopy = mrc.data;
      Real* Mstore = store+(col*(col+3))/2;

      if (i) for (;;)
         { *ColCopy++ = *Mstore; if (!(--i)) break; Mstore += ++col; }
   }
}
