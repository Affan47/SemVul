set_up_simplex_relative(std::vector<vnl_amoeba_SimplexCorner>& simplex,
                                            const vnl_vector<double>& x)
{
  int n = x.size();

  simplex[0].v = x;
  simplex[0].fv = f(x);


  const double usual_delta = relative_diameter;


  for (int j = 0; j < n; ++j) {
    vnl_amoeba_SimplexCorner *s = &simplex[j+1];
    s->v = x;


    if (vnl_math::abs(s->v[j]) > zero_term_delta)
      s->v[j] = (1 + usual_delta)*s->v[j];
    else
      s->v[j] = zero_term_delta;

    s->fv = f(s->v);
  }
}
