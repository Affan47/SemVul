ScalarEval( int j, std::vector<double> &rStack ) const
{
  int n = static_cast<int>(rStack[j+1]);
  try
  {
    rStack[j] = UsefulFunctions::Chisq( rStack[j], n );
  }
  catch (EExpressionError &e)
  {
    throw;
  }
  rStack.pop_back();
}
