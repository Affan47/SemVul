calculateScore(const vector<int>& comps) const
{
  float denom = 1.0 * comps[1];
  float num =  -1.0 * comps[0];
  if ( denom == 0 ) {

    return 1.0;
  } else {
    return (1.0+(num / denom));
  }
}
