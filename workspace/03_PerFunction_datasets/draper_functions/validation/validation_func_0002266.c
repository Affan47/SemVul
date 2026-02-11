perms(const int n){
  if(n<=1){
    Matrix P(1,1);
    P << n;
    P.Release();
    return P;
  }
  Matrix Q = perms(n-1);
  int m = Q.Nrows();
  Matrix P(n*m,n);
  for(int i=1;i<=m;i++){
    P(i,1)=n;
    for(int j=1;j<=Q.Ncols();j++)
      P(i,j+1)=Q(i,j);
  }
  for(int i=n-1;i>=1;i--){
    int jj=1;
    for(int j=(n-i)*m+1;j<=(n-i+1)*m;j++){
      P(j,1)=i;
      for(int k=1;k<=n-1;k++){
	P(j,k+1)= (Q(jj,k)==i) ? n : Q(jj,k);
      }
      jj++;
    }
  }
  P.Release();
  return P;
}
