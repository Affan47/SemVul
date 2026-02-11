laplace_act_gt_m( FMField *out, FMField *gc, FMField *mtx )
{
  int32 iqp, iep, ii, nEP, nQP, nCol;
  float64 *pout, *pmtx, *pg1, *pg2, *pg3;

  nEP = gc->nCol;
  nQP = gc->nLev;
  nCol = mtx->nCol;

  switch (gc->nRow) {
  case 3:
    for (iqp = 0; iqp < nQP; iqp++) {
      pg1 = FMF_PtrLevel( gc, iqp );
      pg2 = pg1 + nEP;
      pg3 = pg2 + nEP;

      pmtx = FMF_PtrLevel( mtx, iqp );
      for (iep = 0; iep < nEP; iep++) {
	pout = FMF_PtrLevel( out, iqp ) + nCol * iep;
	for (ii = 0; ii < nCol; ii++) {
	  pout[ii]
	    = pg1[iep] * pmtx[0*nCol+ii]
	    + pg2[iep] * pmtx[1*nCol+ii]
	    + pg3[iep] * pmtx[2*nCol+ii];
	}
      }
    }
    break;

  case 2:
    for (iqp = 0; iqp < nQP; iqp++) {
      pg1 = FMF_PtrLevel( gc, iqp );
      pg2 = pg1 + nEP;

      pmtx = FMF_PtrLevel( mtx, iqp );
      for (iep = 0; iep < nEP; iep++) {
	pout = FMF_PtrLevel( out, iqp ) + nCol * iep;
	for (ii = 0; ii < nCol; ii++) {
	  pout[ii]
	    = pg1[iep] * pmtx[0*nCol+ii]
	    + pg2[iep] * pmtx[1*nCol+ii];
	}
      }
    }
    break;

  default:
    errput( ErrHead "ERR_Switch\n" );
    return( RET_Fail );
  }

  return( RET_OK );
}
