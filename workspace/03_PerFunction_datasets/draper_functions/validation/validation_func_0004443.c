charGrade(K a, I r)
{
  I n=a->n, b=1+UCHAR_MAX, *c;
  K d=newK(-1,b);U(d)
  c=kI(d);
  K s=newK(-1,n);
  DO(n,c[(UC)kC(a)[i]]++)
  if(!r) DO(b-1,c[i+1]+=c[i])
  else DO(b-1,c[_i-i-2]+=c[_i-i-1])
  DO(n, kI(s)[-1+c[(UC)kC(a)[n-i-1]]--]=n-i-1)
  cd(d);
  R s;
}
