generateCuts(const OsiSolverInterface& si,
				      OsiCuts& cs,
				      const CglTreeInfo )
{


  bool preInit = false;
  bool preReso = false;
  si.getHintParam(OsiDoPresolveInInitial, preInit);
  si.getHintParam(OsiDoPresolveInResolve, preReso);
  if (preInit == false &&  preReso == false && doPreproc_ == -1 ) {
    if (doneInitPre_ == false) {
      mixIntRoundPreprocess(si);
      doneInitPre_ = true;
    }
  }
  else {
    if(doPreproc_ == 1){
      mixIntRoundPreprocess(si);
      doneInitPre_ = true;
    }
    else {
      if (doneInitPre_ == false) {
	mixIntRoundPreprocess(si);
	doneInitPre_ = true;
      }
    }
  }

  const double* xlp        = si.getColSolution();
  const double* colUpperBound = si.getColUpper();
  const double* colLowerBound = si.getColLower();


  const CoinPackedMatrix & tempMatrixByRow = *si.getMatrixByRow();
  CoinPackedMatrix matrixByRow;
  matrixByRow.submatrixOf(tempMatrixByRow, numRows_, indRows_);
  CoinPackedMatrix matrixByCol = matrixByRow;
  matrixByCol.reverseOrdering();

  const double* LHS        = si.getRowActivity();
  const double* coefByRow  = matrixByRow.getElements();
  const int* colInds       = matrixByRow.getIndices();
  const int* rowStarts     = matrixByRow.getVectorStarts();
  const int* rowLengths    = matrixByRow.getVectorLengths();


  const double* coefByCol  = matrixByCol.getElements();
  const int* rowInds       = matrixByCol.getIndices();
  const int* colStarts     = matrixByCol.getVectorStarts();
  const int* colLengths    = matrixByCol.getVectorLengths();


  generateMirCuts(si, xlp, colUpperBound, colLowerBound,
		  matrixByRow, LHS, coefByRow,
		  colInds, rowStarts, rowLengths,
		  coefByCol, rowInds, colStarts, colLengths,
		  cs);
}
