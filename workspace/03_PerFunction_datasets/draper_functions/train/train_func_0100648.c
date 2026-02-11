Make(const TypeOfFE **l,int k) {
  const TypeOfFE** p=new const TypeOfFE*[k];
  for (int i=0;i<k;i++)
    p[i]=l[i];
  return p;
}
