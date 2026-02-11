checkParameterValue (vector<double const *> const &par) const
{
    double p = PROB(par);
    return (SIZE(par) >= 0 && p > 0 && p <= 1);
}
