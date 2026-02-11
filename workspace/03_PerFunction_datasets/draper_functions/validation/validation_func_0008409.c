set(Packet &p)
{
  double d;
  if(p.DecodeFloat(d)) {

    set(d);
  }

}
