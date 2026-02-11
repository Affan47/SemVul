WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {

    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    char buffer[BUFF_SIZE];
    OBMol2Cansmi m2s;

    m2s.Init(true, pConv);

    m2s.CorrectAromaticAmineCharge(mol);


    OBBitVec allbits(mol.NumAtoms());
    FOR_ATOMS_OF_MOL(a, mol) {
      allbits.SetBitOn(a->GetIdx());
    }

    if (mol.NumAtoms() > 0) {
      CreateCansmiString(mol, buffer, allbits, !pConv->IsOption("i"), pConv);
    }
    ofs << buffer << endl;

    OBAtom *atom;
    vector<int>::iterator i;

    string orderString = m2s.GetOutputOrder();
    vector<string> canonical_order;
    tokenize(canonical_order, orderString);

    int j;
    int atomIdx;
    for (j = 0;j < mol.NumConformers();j++)
      {
        mol.SetConformer(j);
        for (unsigned int index = 0; index < canonical_order.size();
             ++index) {
          atomIdx = atoi(canonical_order[index].c_str());
          atom = mol.GetAtom(atomIdx);
          sprintf(buffer,"%9.3f %9.3f %9.3f",atom->GetX(),atom->GetY(),atom->GetZ());
          ofs << buffer<< endl;
        }
      }
    return(true);
  }
