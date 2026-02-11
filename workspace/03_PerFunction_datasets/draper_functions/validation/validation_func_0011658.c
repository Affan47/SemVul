accept(vector<int> id) {
  bool allowed(false);

  if(id.size()!=5){return false;}
  int npiminus=0,npiplus=0,npi0=0;
  for(unsigned int ix=0;ix<id.size();++ix) {
    if(id[ix]==ParticleID:: piplus){++npiplus;}
    else if(id[ix]==ParticleID::piminus){++npiminus;}
    else if(id[ix]==ParticleID::pi0){++npi0;}
  }
  if(npiplus>npiminus) swap(npiplus,npiminus);
  if(     npiminus==3&&npiplus==2&&npi0==0) allowed=true;
  else if(npiminus==2&&npiplus==1&&npi0==2) allowed=true;
  else if(npiminus==1&&npiplus==0&&npi0==4) allowed=true;
  return allowed;
}
