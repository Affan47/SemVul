conn_comp(int n, SparseMatrix A, int *groups, SparseMatrix *poly_point_map){

  int *ia, *ja;
  int one = 1, jj, i, j;
  SparseMatrix B, BB;
  int ncomps, *comps = NULL, *comps_ptr = NULL;

  B = SparseMatrix_new(n, n, 1, MATRIX_TYPE_INTEGER, FORMAT_COORD);
  ia = A->ia;
  ja = A->ja;
  for (i = 0; i < n; i++){
    for (j = ia[i]; j < ia[i+1]; j++){
      jj = ja[j];
      if (i != jj && groups[i] == groups[jj]){
	SparseMatrix_coordinate_form_add_entries(B, 1, &i, &jj, &one);
      }
    }
  }
  BB = SparseMatrix_from_coordinate_format(B);

  SparseMatrix_weakly_connected_components(BB, &ncomps, &comps, &comps_ptr);
  SparseMatrix_delete(B);
  SparseMatrix_delete(BB);
  *poly_point_map = SparseMatrix_new(ncomps, n, n, MATRIX_TYPE_PATTERN, FORMAT_CSR);
  FREE((*poly_point_map)->ia);
  FREE((*poly_point_map)->ja);
  (*poly_point_map)->ia = comps_ptr;
  (*poly_point_map)->ja = comps;
  (*poly_point_map)->nz = n;

}
