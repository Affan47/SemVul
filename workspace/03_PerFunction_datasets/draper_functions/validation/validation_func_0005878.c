LineBracket(double *x1, double *x2, double *x3,
              double *f1, double *f2, double *f3)
{
  PowellOptimizer::ParametersType tempCoord(m_SpaceDimension);

  this->LineBracket(x1, x2, x3, f1, f2, f3, tempCoord);
}
