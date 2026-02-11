testIdsAddAtom()
{
  OBMol mol;

  for (int i = 0; i < 5; ++i)
    mol.NewAtom();

  OBAtom a;
  a.SetAtomicNum(6);

  mol.AddAtom(a);

  OB_REQUIRE( mol.NumAtoms() == 6 );
  OB_REQUIRE( mol.GetAtomById(5) );
  OB_REQUIRE( mol.GetAtomById(5)->GetId() == 5 );
}
