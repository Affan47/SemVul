setup_basis_func_polys(IntegralInfo* b)
{
  basis_func_poly_struct* curr = NULL;
  int count = 0;

  const int MAX_L_QUANTUM_NUMBER = BASIS_FUNC_POLY_MAX_DEGREE;
  ergo_real scaleFactorList[MAX_L_QUANTUM_NUMBER+1];
  scaleFactorList[0] = 1;
  scaleFactorList[1] = 1;
  scaleFactorList[2] = std::sqrt(3.0);
  scaleFactorList[3] = std::sqrt(15.0);

  for(int ii = 4; ii <= MAX_L_QUANTUM_NUMBER; ii++)
    scaleFactorList[ii] = std::sqrt(15.0);

  for(int l = 0; l <= MAX_L_QUANTUM_NUMBER; l++) {
    for(int m = -l; m <= l; m++) {
      curr = &b->basis_func_poly_list[count];
      if(get_real_solid_harmonic_poly(l, m, curr) != 0) {
	do_output(LOG_CAT_ERROR, LOG_AREA_INTEGRALS, "error in get_real_solid_harmonic_poly");
	return -1;
      }


      if(m == 0)
	curr->scaledSolidHarmonicPrefactor = 1;
      else
	curr->scaledSolidHarmonicPrefactor = std::pow((ergo_real)-1, m) / std::sqrt((ergo_real)2);


      for(int i = 0; i < curr->noOfTerms; i++)
	curr->termList[i].coeff /= scaleFactorList[l];


      curr->scaledSolidHarmonicPrefactor *= scaleFactorList[l];

      count++;
      if(count >= MAX_NO_OF_BASIS_FUNC_POLYS) {
	do_output(LOG_CAT_ERROR, LOG_AREA_INTEGRALS,
		  "error in setup_basis_func_polys: (count >= MAX_NO_OF_BASIS_FUNC_POLYS)");
	return -1;
      }
    }
  }


  for(int j = 0; j < count; j++) {
    curr = &b->basis_func_poly_list[j];
    for(int i = 0; i < curr->noOfTerms; i++) {
      basis_func_term_struct* currTerm = &curr->termList[i];
      int i0 = currTerm->monomialInts[0];
      int i1 = currTerm->monomialInts[1];
      int i2 = currTerm->monomialInts[2];
      currTerm->monomialID = b->monomial_info.monomial_index_list[i0][i1][i2];
    }
  }

  b->no_of_basis_func_polys = count;

  return 0;
}
