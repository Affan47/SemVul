extractEWallIGP(AMPIBuffer* B)
{
  string name=B->pop_string();
  double k=B->pop_double();
  string wname=B->pop_string();
  CEWallIGP* res=new CEWallIGP(name,wname,k);
  return res;
}
