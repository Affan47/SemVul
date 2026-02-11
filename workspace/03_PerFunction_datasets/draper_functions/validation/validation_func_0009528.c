IsCarboxylOxygen()
  {
    if (!IsOxygen())
      return(false);
    if (GetHvyValence() != 1)
      return(false);

    OBAtom *atom;
    OBBond *bond;
    OBBondIterator i;

    atom = NULL;
    for (bond = BeginBond(i);bond;bond = NextBond(i))
      if ((bond->GetNbrAtom(this))->IsCarbon())
        {
          atom = bond->GetNbrAtom(this);
          break;
        }
    if (!atom)
      return(false);
    if (!(atom->CountFreeOxygens() == 2)
      && !(atom->CountFreeOxygens() == 1 && atom->CountFreeSulfurs() == 1))
      return(false);


    return(true);
  }
