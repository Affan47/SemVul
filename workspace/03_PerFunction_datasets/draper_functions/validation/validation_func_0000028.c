nlSparseMatrixMult(NLSparseMatrix* A, NLdouble* x, NLdouble* y) {
    if(A->storage & NL_MATRIX_STORE_ROWS) {
        if(A->storage & NL_MATRIX_STORE_SYMMETRIC) {
            nlSparseMatrix_mult_rows_symmetric(A, x, y) ;
        } else {
            nlSparseMatrix_mult_rows(A, x, y) ;
        }
    } else {
        if(A->storage & NL_MATRIX_STORE_SYMMETRIC) {
            nlSparseMatrix_mult_cols_symmetric(A, x, y) ;
        } else {
            nlSparseMatrix_mult_cols(A, x, y) ;
        }
    }
}
