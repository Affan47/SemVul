dataBaseOutput(ofstream & output,bool header) const {

  if(header) output << "update decayers set parameters=\"";
  output << "newdef " << name() << ":Iteration " << _niter << "\n";
  output << "newdef " << name() << ":Ntry " << _ntry << "\n";
  output << "newdef " << name() << ":Points " << _npoint << "\n";

  output << "newdef " << name() << ":GenerateIntermediates " << _generateinter << " \n";

  if(header) {
    output << "\n\" where BINARY ThePEGName=\"" << fullName() << "\";\n";
  }
}
