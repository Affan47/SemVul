EvaluateCDF(double x) const
{
  if ( m_Parameters.GetSize() != 1 )
    {
    itkGenericExceptionMacro(
      "Invalid number of parameters to describe distribution. Expected 1 parameter, but got "
      << m_Parameters.size()
      << " parameters.");
    }
  return TDistribution::CDF( x, static_cast< SizeValueType >( m_Parameters[0] ) );
}
