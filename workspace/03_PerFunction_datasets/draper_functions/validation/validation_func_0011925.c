readLp(FILE *fp, const double epsilon) {
  CoinLpIO m;
  m.readLp(fp, epsilon);


  setDblParam(OsiObjOffset, 0);


  setStrParam(OsiProbName, m.getProblemName());


  loadProblem(*m.getMatrixByRow(), m.getColLower(), m.getColUpper(),
	      m.getObjCoefficients(), m.getRowLower(), m.getRowUpper());
  setRowColNames(m) ;
  const char *integer = m.integerColumns();
  if (integer) {
    int i, n = 0;
    int nCols = m.getNumCols();
    int *index = new int [nCols];
    for (i=0; i<nCols; i++) {
      if (integer[i]) {
	index[n++] = i;
      }
    }
    setInteger(index, n);
    delete [] index;
  }
  setObjSense(1);
  return(0);
}
