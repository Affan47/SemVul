qbargME(vector<SpinorBarWaveFunction> & ain,
			      vector<VectorWaveFunction>    & gin,
			      vector<VectorWaveFunction>    & pout,
			      vector<SpinorWaveFunction>    & aout,
			      bool calc) const {


  ProductionMatrixElement newme(PDT::Spin1Half,PDT::Spin1,
				PDT::Spin1,PDT::Spin1Half);

  SpinorBarWaveFunction inter;
  SpinorWaveFunction interb;
  unsigned int inhel1,inhel2,outhel1,outhel2;
  Energy2 mt(scale());
  Complex diag[3];
  double me(0.),diag1(0.),diag2(0.);
  for(inhel1=0;inhel1<2;++inhel1) {
    for(inhel2=0;inhel2<2;++inhel2) {
      for(outhel1=0;outhel1<2;++outhel1) {
	for(outhel2=0;outhel2<2;++outhel2) {

	  inter = _photonvertex->evaluate(ZERO,5,ain[inhel1].particle()->CC(),
					  ain[inhel1],pout[outhel1]);
	  diag[0]=_gluonvertex->evaluate(mt,aout[outhel2],inter,gin[inhel2]);

	  inter = _gluonvertex->evaluate(mt,5,ain[inhel1].particle()->CC(),
					 ain[inhel1],gin[inhel2]);
	  diag[1]=_photonvertex->evaluate(ZERO,aout[outhel2],inter,pout[outhel1]);

	  diag[2]=diag[0]+diag[1];
	  diag1 +=norm(diag[0]);
	  diag2 +=norm(diag[1]);
	  me    +=norm(diag[2]);

	  if(calc) newme(inhel1,2*inhel2,2*outhel1,outhel2)=diag[2];
	}
      }
    }
  }

  if(!calc) {
    DVector save;
    save.push_back(diag1);
    save.push_back(diag2);
    meInfo(save);
  }

  if(calc) _me.reset(newme);
  return me;
}
