add_influence_source(int pos, int color, float strength, float attenuation,
                     struct influence_data *q)
{
  if ((color & WHITE) && (q->white_strength[pos] < strength)) {
    q->white_strength[pos] = strength;
    q->white_attenuation[pos] = attenuation;
  }

  if ((color & BLACK) && (q->black_strength[pos] < strength)) {
    q->black_strength[pos] = strength;
    q->black_attenuation[pos] = attenuation;
  }
}
