scalarProduct(size_t a, size_t b,
					const vector<PDT::Colour>& abBasis) const {

  if ( id33bar.empty() )
    makeIds();

  if ( abBasis == id33bar ) {
    assert(a==b);
    return SM().Nc();
  }

  if ( abBasis == id33bar8 ) {
    assert(a==b);
    return (SM().Nc()*SM().Nc()-1.)/2.;
  }

  if ( abBasis == id33bar88 ) {
    if ( a == b ) {
      return sqr((SM().Nc()*SM().Nc()-1.)/2.)/SM().Nc();
    }
    return (1.-SM().Nc()*SM().Nc())/(4.*SM().Nc());
  }

  if ( abBasis == id33bar33bar ) {
    if ( a == b )
      return SM().Nc()*SM().Nc();
    return SM().Nc();
  }

  throw Exception() << "Cannot handle colour configuration" << Exception::abortnow;

}
