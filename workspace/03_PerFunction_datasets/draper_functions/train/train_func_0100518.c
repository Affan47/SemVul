computeTemporaryTerms(map<expr_t, int> &reference_count,
                                     temporary_terms_t &temporary_terms,
                                     bool is_matlab) const
{
  expr_t this2 = const_cast<TrinaryOpNode *>(this);
  map<expr_t, int>::iterator it = reference_count.find(this2);
  if (it == reference_count.end())
    {


      reference_count[this2] = 1;
      arg1->computeTemporaryTerms(reference_count, temporary_terms, is_matlab);
      arg2->computeTemporaryTerms(reference_count, temporary_terms, is_matlab);
      arg3->computeTemporaryTerms(reference_count, temporary_terms, is_matlab);
    }
  else
    {


      reference_count[this2]++;
      if (reference_count[this2] * cost(temporary_terms, is_matlab) > MIN_COST(is_matlab))
        temporary_terms.insert(this2);
    }
}
