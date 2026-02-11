classify(const Sample & nbs, vector<double> & membp) const
{

  assert(_num_classes == (int)membp.size());
  conditional_probability(nbs, membp);
  int max_label = 0;
  double max = 0.0;
  for (int i = 0; i < (int)membp.size(); i++) {

    if (membp[i] > max) { max_label = i; max = membp[i]; }
  }

  return max_label;
}
