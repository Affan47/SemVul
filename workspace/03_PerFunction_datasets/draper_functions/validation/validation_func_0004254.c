testAutomorphismPreMapping()
{
  cout <<  "testAutomorphismPreMapping" << endl;
  OBMol mol;
  OBConversion conv;
  conv.SetInFormat("smi");
  conv.ReadString(&mol, "c1(C)c(C)c(C)c(C)c(C)c1");

  Automorphisms aut;
  FindAutomorphisms((OBMol*)&mol, aut);
  cout << aut.size() << endl;
  OB_ASSERT( aut.size() == 2 );
}
