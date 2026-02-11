CL(const ShowerParticleVector::const_iterator & a, unsigned int index=0) {
    return (*a)->colourInfo()->colourLines().empty() ? ThePEG::tColinePtr() :
      const_ptr_cast<ThePEG::tColinePtr>((*a)->colourInfo()->colourLines()[index]);
  }
