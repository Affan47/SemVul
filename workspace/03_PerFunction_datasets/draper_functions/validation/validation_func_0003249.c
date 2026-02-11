ccp(C *d,const C *s)
{
  C *t=d;
  for(;*d=*s;++d,++s)
    if(*s=='\\')
      if(*++s=='n')*d=10;
      else if(!isdi(*s))*d=*s;
      else
      {
	I j=3,n=*s-'0';
	for(;isdi(*++s)&&--j;n=n*8+*s-'0');
	--s,*d=n;
      }
  R d-t;
}
