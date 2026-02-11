collapseToMeson() {


  if (mSys < 1.001 * mhvMeson) {
    infoPtr->errorMsg("Error in HiddenValleyFragmentation::collapseToMeson:"
      " too low mass to do anything");
    return false;
  }


  double mhvGlue = (0.001 + 0.998 * rndmPtr->flat()) * (mSys - mhvMeson);


  double pAbs = 0.5 * sqrtpos( pow2(mSys*mSys - mhvMeson*mhvMeson
    - mhvGlue*mhvGlue) - pow2(2. * mhvMeson * mhvGlue) ) / mSys;
  double pz   = (2 * rndmPtr->flat() - 1.) * pAbs;
  double pT   = sqrtpos( pAbs*pAbs - pz*pz);
  double phi  = 2. * M_PI * rndmPtr->flat();
  double px   = pT * cos(phi);
  double py   = pT * sin(phi);


  Vec4 phvMeson( px, py, pz, sqrt(mhvMeson*mhvMeson + pAbs*pAbs) );
  Vec4 phvGlue( -px, -py, -pz, sqrt(mhvGlue*mhvGlue + pAbs*pAbs) );
  phvMeson.bst( hvColConfig[0].pSum );
  phvGlue.bst(  hvColConfig[0].pSum );


  vector<int> iParton = hvColConfig[0].iParton;
  int iFirst = hvEvent.append( 4900111, 82,  iParton.front(),
    iParton.back(), 0, 0, 0, 0, phvMeson, mhvMeson);
  int iLast  = hvEvent.append( 4900991, 82,  iParton.front(),
    iParton.back(), 0, 0, 0, 0, phvGlue, mhvGlue);


  for (int i = 0; i < int(iParton.size()); ++i) {
    hvEvent[ iParton[i] ].statusNeg();
    hvEvent[ iParton[i] ].daughters(iFirst, iLast);
  }


  return true;

}
