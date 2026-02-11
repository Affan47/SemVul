replaceColumnPFI ( CoinIndexedVector * regionSparse,
				      int pivotRow,
				      double alpha)
{
  CoinBigIndex *startColumn=startColumnU_.array()+numberRows_;
  int *indexRow=indexRowU_.array();
  CoinFactorizationDouble *element=elementU_.array();
  CoinFactorizationDouble * pivotRegion = pivotRegion_.array()+numberRows_;

  const double *region = regionSparse->denseVector (  );
  const int * index = regionSparse->getIndices();
  int numberNonZero = regionSparse->getNumElements();

  int iColumn = numberPivots_;

  if (!iColumn)
    startColumn[0]=startColumn[maximumColumnsExtra_];
  CoinBigIndex start = startColumn[iColumn];


  if ( numberPivots_ >= maximumPivots_ ) {
    return 5;
  }
  if ( lengthAreaU_ - ( start + numberNonZero ) < 0) {
    return 3;
  }

  int i;
  if (numberPivots_) {
    if (fabs(alpha)<1.0e-5) {
      if (fabs(alpha)<1.0e-7)
	return 2;
      else
	return 1;
    }
  } else {
    if (fabs(alpha)<1.0e-8)
      return 2;
  }
  CoinFactorizationDouble pivotValue = 1.0/alpha;
  pivotRegion[iColumn]=pivotValue;
  double tolerance = zeroTolerance_;
  const int * pivotColumn = pivotColumn_.array();

  if (regionSparse->packedMode()) {
    for ( i = 0; i < numberNonZero; i++ ) {
      int iRow = index[i];
      if (iRow!=pivotRow) {
	if ( fabs ( region[i] ) > tolerance ) {
	  indexRow[start]=pivotColumn[iRow];
	  element[start++]=region[i]*pivotValue;
	}
      }
    }
  } else {
    for ( i = 0; i < numberNonZero; i++ ) {
      int iRow = index[i];
      if (iRow!=pivotRow) {
	if ( fabs ( region[iRow] ) > tolerance ) {
	  indexRow[start]=pivotColumn[iRow];
	  element[start++]=region[iRow]*pivotValue;
	}
      }
    }
  }
  numberPivots_++;
  numberNonZero=start-startColumn[iColumn];
  startColumn[numberPivots_]=start;
  totalElements_ += numberNonZero;
  int * pivotColumn2 = pivotColumn_.array()+numberRows_;
  pivotColumn2[iColumn]=pivotColumn[pivotRow];
  return 0;
}
