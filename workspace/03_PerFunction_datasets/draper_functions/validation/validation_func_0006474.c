setIdColAcol() {


  int idq           = (id2 == 22) ? id1 : id2;
  int sign          = 1 - 2 * (abs(idq)%2);
  if (idq < 0) sign = -sign;
  id4 = couplingsPtr->V2CKMpick(idq);


  setId( id1, id2, 24 * sign, id4);


  swapTU = (id2 == 22);


  if      (abs(id1) < 9) setColAcol( 1, 0, 0, 0, 0, 0, 1, 0);
  else if (abs(id2) < 9) setColAcol( 0, 0, 1, 0, 0, 0, 1, 0);
  else                   setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if (idq < 0) swapColAcol();

}
