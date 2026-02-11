_dxfAssociateInteractorEcho (tdmInteractor T, tdmInteractor A)
{
  ENTRY(("_dxfAssociateInteractorEcho(0x%x, 0x%x)", T, A));


  if (T) AUX(T) = A ;
  if (A) IS_AUX(A) = 1 ;

  EXIT((""));
}
