doinit() {

  for(long ix=1;ix<7;++ix){
    addToList( ParticleID::SUSY_Gravitino,  ix, -(1000000+ix) );
    addToList( ParticleID::SUSY_Gravitino,  ix, -(2000000+ix) );
    addToList( ParticleID::SUSY_Gravitino, -ix,  (1000000+ix) );
    addToList( ParticleID::SUSY_Gravitino, -ix,  (2000000+ix) );
  }

  for(long ix=11;ix<17;++ix) {
    addToList( ParticleID::SUSY_Gravitino,  ix, -(1000000+ix) );
    addToList( ParticleID::SUSY_Gravitino, -ix,  (1000000+ix) );

    if( ix % 2 != 0 ) {
      addToList( ParticleID::SUSY_Gravitino,  ix, -(2000000+ix) );
      addToList( ParticleID::SUSY_Gravitino, -ix,  (2000000+ix) );
    }
  }
  RFSVertex::doinit();
  tMSSMPtr model = dynamic_ptr_cast<tMSSMPtr>(generator()->standardModel());
  if( !model )
    throw InitException() << "SSGVFSVertex::doinit() - "
			  << "The model pointer is null."
			  << Exception::abortnow;
  MPlanck_ = model->MPlanck();
  stop_ = model->stopMix();
  sbot_ = model->sbottomMix();
  stau_ = model->stauMix();
}
