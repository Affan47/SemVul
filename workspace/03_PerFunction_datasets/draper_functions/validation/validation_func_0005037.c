get_score(GtScoreMatrix *score_matrix,
                        GtAlphabet *score_matrix_alphabet,
                        unsigned char amino,
                        unsigned char origreferencechar)
{
  GthFlt rval = 0.0,
         scalefactor   = SCALEFACTOR,
         indel_penalty = INDEL_PENALTY;

  if (amino  == DASH || origreferencechar == DASH) {


    rval = scalefactor * indel_penalty;
  }
  else if (amino != WILDCARD && amino <= CHAR_MAX &&
           gt_alphabet_valid_input(score_matrix_alphabet, amino) &&
           origreferencechar <= CHAR_MAX &&
           gt_alphabet_valid_input(score_matrix_alphabet,
                                   origreferencechar)) {

    if (amino == GT_STOP_AMINO) {

      if (origreferencechar == GT_STOP_AMINO)
        rval = scalefactor * -2 * indel_penalty;
      else
        rval = scalefactor *  2 * indel_penalty;
    }
    else {

      if (origreferencechar == GT_STOP_AMINO)
        rval = scalefactor *  2 * indel_penalty;
      else {
        GtUchar code1, code2;
        int wcidx;
        code1 = gt_alphabet_encode(score_matrix_alphabet, amino);
        code2 = gt_alphabet_encode(score_matrix_alphabet, origreferencechar);
        wcidx = gt_alphabet_size(score_matrix_alphabet) - 1;
        rval = scalefactor *
               gt_score_matrix_get_score(score_matrix,
                                         code1 == WILDCARD ? wcidx : code1,
                                         code2 == WILDCARD ? wcidx : code2);
      }
    }
  }


  return rval;
}
