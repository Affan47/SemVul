dataBaseOutput(ofstream & output,
						      bool header) const {
  if(header) output << "update decayers set parameters=\"";
  Baryon1MesonDecayerBase::dataBaseOutput(output,false);
  output << "newdef " << name() << ":Fcoupling " << _sf << "\n";
  output << "newdef " << name() << ":Dcoupling " << _sd << "\n";
  output << "newdef " << name() << ":Parity " << _parity<< "\n";
  output << "newdef " << name() << ":Fpi " << _fpi/MeV << "\n";
  output << "newdef " << name() << ":Proton " << _proton << "\n";
  output << "newdef " << name() << ":Neutron " << _neutron << "\n";
  output << "newdef " << name() << ":Sigma+ " << _sigmap << "\n";
  output << "newdef " << name() << ":Sigma0 " << _sigma0 << "\n";
  output << "newdef " << name() << ":Sigma- " << _sigmam << "\n";
  output << "newdef " << name() << ":Lambda " << _lambda << "\n";
  output << "newdef " << name() << ":Xi0 " << _xi0 << "\n";
  output << "newdef " << name() << ":Xi- " << _xim << "\n";
  output << "newdef " << name() << ":ExcitedProton " << _eproton << "\n";
  output << "newdef " << name() << ":ExcitedNeutron " << _eneutron << "\n";
  output << "newdef " << name() << ":ExcitedSigma+ " << _esigmap << "\n";
  output << "newdef " << name() << ":ExcitedSigma0 " << _esigma0 << "\n";
  output << "newdef " << name() << ":ExcitedSigma- " << _esigmam << "\n";
  output << "newdef " << name() << ":ExcitedLambda " << _elambda << "\n";
  output << "newdef " << name() << ":ExcitedXi0 " << _exi0 << "\n";
  output << "newdef " << name() << ":ExcitedXi- " << _exim << "\n";
  for(unsigned int ix=0;ix<_maxweight.size();++ix) {
    output << "insert " << name() << ":MaxWeight " << ix << " "
	   << _maxweight[ix] << "\n";
  }
  if(header) output << "\n\" where BINARY ThePEGName=\""
		    << fullName() << "\";" << endl;
}
