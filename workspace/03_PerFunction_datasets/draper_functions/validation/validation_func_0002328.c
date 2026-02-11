getRightHandSide() const
{
  if ( rhs_==NULL ) {

    int nr=numberRows_;
    rhs_ = reinterpret_cast<double *> (malloc(nr*sizeof(double)));


    char dum1;
    double dum2;
    int i;
    for ( i=0; i<nr; i++ ) {
      convertBoundToSense(rowlower_[i],rowupper_[i],dum1,rhs_[i],dum2);
    }
  }
  return rhs_;
}
