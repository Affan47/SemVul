compareBeamParticles( GenEvent* e1, GenEvent* e2 ) {
   GenParticle* e1b1 = e1->beam_particles().first;
   GenParticle* e1b2 = e1->beam_particles().second;
   GenParticle* e2b1 = e2->beam_particles().first;
   GenParticle* e2b2 = e2->beam_particles().second;
   if( e1b1 && e1b2 && e2b1 && e2b2 ) {
       if( (*e1b1) == (*e2b1)  && (*e1b2) == (*e2b2) ) {
       } else {
	   std::cerr << "compareBeamParticles: beam particles differ " << std::endl;
	   return false;
       }
   }
   return true;
}
