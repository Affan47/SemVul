test_alignWithoutHydrogens() {
  OBConversion conv;
  bool success = conv.SetInFormat("xyz");
  OB_REQUIRE( success );

  OBMol mol;
  success = conv.ReadFile(&mol, TESTDATADIR + string("test3d.xyz"));
  OB_REQUIRE( success );


  OBAlign align = OBAlign(mol, mol, false, false);
  align.Align();
  double rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 1.0E-6 );


  OBMol clone = mol;
  OBAtom *atom = clone.GetAtom(8);
  OB_REQUIRE( atom->IsHydrogen() );
  atom->SetVector(atom->GetVector() + vector3(0.1, 0.1, 0.1));

  matrix3x3 rot;
  rot.RotAboutAxisByAngle(vector3(1.0, -0.3, 0.23), 67);
  double rot_array[9];
  rot.GetArray(rot_array);
  clone.Rotate(rot_array);


  OB_ASSERT( !clone.GetAtom(1)->GetVector().IsApprox(mol.GetAtom(1)->GetVector(), 1.0E-8) );


  align = OBAlign(mol, clone, true, false);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) > 1.0E-3 );
  vector<vector3> result = align.GetAlignment();
  OB_ASSERT( result.size() == mol.NumAtoms() );


  align = OBAlign(mol, clone, false, false);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 1.0E-6 );
  result = align.GetAlignment();
  OB_ASSERT( result.size() == mol.NumAtoms() );
  OB_ASSERT( result.at(0).IsApprox( mol.GetAtom(1)->GetVector(), 1.0E-8 ) );


  align = OBAlign(mol, clone, false, true);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 1.0E-6 );
  result = align.GetAlignment();
  OB_ASSERT( result.size() == mol.NumAtoms() );
  OB_ASSERT( result.at(0).IsApprox( mol.GetAtom(1)->GetVector(), 1.0E-8 ) );
}
