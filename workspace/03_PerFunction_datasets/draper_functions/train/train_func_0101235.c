analyze(tEventPtr event, long, int, int) {


  Lorentz5Momentum p1, p2, ppair;
  bool foundphotons = false;
  set<tcPPtr> particles;
  event->selectFinalState(inserter(particles));

  for(set<tcPPtr>::const_iterator it = particles.begin();
      it != particles.end(); ++it) {
    if((**it).id()==ParticleID::gamma) {

      if( getMomentum(*it).perp() > p2.perp() ) {
	if (getMomentum(*it).perp() > p1.perp()) {
	  p2 = p1;
	  p1 = getMomentum(*it);
	} else {
	  p2 = getMomentum(*it);
	}
      }
    }
  }


  if (p1.perp()/GeV > 0 && p2.perp()/GeV > 0) foundphotons = true;

  ppair = p1 + p2;
  if (foundphotons) {
    _ptharder += p1.perp()/GeV;
    _ptsofter += p2.perp()/GeV;
    _ptpair += ppair.perp()/GeV;
    _Eharder += p1.e()/GeV;
    _Esofter += p2.e()/GeV;
    _Epair += ppair.e()/GeV;
    _rapharder += p1.rapidity();
    _rapsofter += p2.rapidity();
    _rappair += ppair.rapidity();
    _phiharder += p1.phi();
    _phisofter += p2.phi();
    _deltaphi += (p2.vect()).deltaPhi(p1.vect());
    _mpair += ppair.m()/GeV;
  } else {
    cerr << "Analysis/GammaGammaAnalysis: Found no hard photon in event "
	 << event->number()  << ".\n";
    generator()->log() << "Analysis/GammaGammaAnalysis: "
		       << "Found no hard photon in event "
		       << event->number()  << ".\n"
		       << *event;
  }
}
