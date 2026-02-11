svdWriteSparseMatrix(SMat S, char *filename, int format) {
  DMat D = NULL;
  FILE *file = svd_writeFile(filename, FALSE);
  if (!file) {
    svd_error("svdWriteSparseMatrix: failed to write file %s\n", filename);
    return;
  }
  switch (format) {
  case SVD_F_STH:
    svdWriteSparseTextHBFile(S, file);
    break;
  case SVD_F_ST:
    svdWriteSparseTextFile(S, file);
    break;
  case SVD_F_SB:
    svdWriteSparseBinaryFile(S, file);
    break;
  case SVD_F_DT:
    D = svdConvertStoD(S);
    svdWriteDenseTextFile(D, file);
    break;
  case SVD_F_DB:
    D = svdConvertStoD(S);
    svdWriteDenseBinaryFile(D, file);
    break;
  default: svd_error("svdLoadSparseMatrix: unknown format %d", format);
  }
  svd_closeFile(file);
  if (D) svdFreeDMat(D);
}
