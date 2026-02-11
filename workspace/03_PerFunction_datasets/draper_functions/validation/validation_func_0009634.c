fractions_deriv(const int& nfib, const ColumnVector& fs, const ColumnVector& bs) const{
  NEWMAT::Matrix Deriv(nfib,nfib);
  float fsum;
  Deriv=0;
  for (int j=1; j<=nfib; j++)
    for (int k=1; k<=nfib; k++){
      if (j==k){
	fsum=1;
	for (int n=1; n<=j-1; n++)
	  fsum-=fs(n);
	Deriv(j,k)=sin(2*bs(k))*fsum;
      }
      else if (j>k){
	fsum=0;
	for (int n=1; n<=j-1; n++)
	  fsum+=Deriv(n,k);
	Deriv(j,k)=-pow(sin(bs(j)),2.0)*fsum;
      }
    }
  Deriv.Release();
  return Deriv;
}
