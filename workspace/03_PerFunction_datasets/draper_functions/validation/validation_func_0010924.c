prepareForDerivation()
{
  if (preparedForDerivation)
    return;

  preparedForDerivation = true;

  arg1->prepareForDerivation();
  arg2->prepareForDerivation();
  arg3->prepareForDerivation();


  set<int> non_null_derivatives_tmp;
  set_union(arg1->non_null_derivatives.begin(),
            arg1->non_null_derivatives.end(),
            arg2->non_null_derivatives.begin(),
            arg2->non_null_derivatives.end(),
            inserter(non_null_derivatives_tmp, non_null_derivatives_tmp.begin()));
  set_union(non_null_derivatives_tmp.begin(),
            non_null_derivatives_tmp.end(),
            arg3->non_null_derivatives.begin(),
            arg3->non_null_derivatives.end(),
            inserter(non_null_derivatives, non_null_derivatives.begin()));
}
