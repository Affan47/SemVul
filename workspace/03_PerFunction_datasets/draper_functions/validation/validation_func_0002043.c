WriteChem3d(ostream &ofs,OBMol &mol, const char *mol_typ)
  {
    int atnum;
    int type_num;
    char buffer[BUFF_SIZE],type_name[16],ele_type[16];

    ofs << mol.NumAtoms();
    if (EQ(mol_typ,"MMADS"))
      {
        ofs << " " << mol.GetTitle();
        ttab.SetToType("MM2");
      }
    else
      ttab.SetToType(mol_typ);
    ofs << endl;

    ttab.SetFromType("INT");

    OBAtom *atom,*nbr;
    vector<OBAtom*>::iterator i;
    vector<OBBond*>::iterator j;

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        if (!ttab.Translate(type_name,atom->GetType()))
          {
            snprintf(buffer, BUFF_SIZE,
                     "Unable to assign %s type to atom %d type = %s\n",
                     mol_typ,atom->GetIdx(),atom->GetType());
            obErrorLog.ThrowError(__FUNCTION__, buffer, obInfo);
            atnum = atom->GetAtomicNum();
            type_num = atnum * 10 + atom->GetValence();
            snprintf(type_name, sizeof(type_num), "%d",type_num);
          }
        strncpy(ele_type, etab.GetSymbol(atom->GetAtomicNum()), sizeof(ele_type));
        ele_type[sizeof(ele_type) - 1] = '\0';
        snprintf(buffer, BUFF_SIZE, "%-3s %-5d %8.4f  %8.4f  %8.4f %5s",
                ele_type,
                atom->GetIdx(),
                atom->x(),
                atom->y(),
                atom->z(),
                type_name);
        ofs << buffer;

        for (nbr = atom->BeginNbrAtom(j);nbr;nbr = atom->NextNbrAtom(j))
          {
            snprintf(buffer, BUFF_SIZE, "%6d",nbr->GetIdx());
            ofs << buffer;
          }
        ofs << endl;
      }
    return(true);
  }
