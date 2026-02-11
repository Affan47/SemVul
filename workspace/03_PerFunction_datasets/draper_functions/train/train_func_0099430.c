SaveVec(KN<double> *const & f, string *const & nome)
{
  std::ofstream outfile (nome->data(),ios_base::binary);


  long int nn = f->N();
  long int dim=nn;
  outfile.write ((char*) &dim, sizeof(long int));
  double ftemp ;
  for(long int i=0; i<nn; i++) {

    ftemp = *(f[0]+i) ;
    outfile.write ((char*) &ftemp, sizeof(double));
  }
  outfile.close();
  return 0.0;
}
