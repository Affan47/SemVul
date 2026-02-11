shoot(HepRandomEngine* anEngine, double xm) {


  double em, t, y;
  double sq, alxm, g1;
  double om = getOldMean();

  double* status = getPStatus();
  sq = status[0];
  alxm = status[1];
  g1 = status[2];

  if( xm == -1 ) return 0;
  if( xm < 12.0 ) {
    if( xm != om ) {
      setOldMean(xm);
      g1 = std::exp(-xm);
    }
    em = -1;
    t = 1.0;
    do {
      em += 1.0;
      t *= anEngine->flat();
    } while( t > g1 );
  }
  else if ( xm < getMaxMean() ) {
    if ( xm != om ) {
      setOldMean(xm);
      sq = std::sqrt(2.0*xm);
      alxm = std::log(xm);
      g1 = xm*alxm - gammln(xm + 1.0);
    }
    do {
      do {
	y = std::tan(CLHEP::pi*anEngine->flat());
	em = sq*y + xm;
      } while( em < 0.0 );
      em = std::floor(em);
      t = 0.9*(1.0 + y*y)* std::exp(em*alxm - gammln(em + 1.0) - g1);
    } while( anEngine->flat() > t );
  }
  else {
    em = xm + std::sqrt(xm) * normal (anEngine);
    if ( static_cast<long>(em) < 0 )
      em = static_cast<long>(xm) >= 0 ? xm : getMaxMean();
  }
  setPStatus(sq,alxm,g1);
  return long(em);
}
