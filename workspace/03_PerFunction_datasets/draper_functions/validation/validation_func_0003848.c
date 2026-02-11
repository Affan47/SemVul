DeleteHydrogens()
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator i;
    vector<OBAtom*> delatoms,va;

    obErrorLog.ThrowError(__FUNCTION__,
                          "Ran OpenBabel::DeleteHydrogens", obAuditMsg);

    for (atom = BeginAtom(i);atom;atom = NextAtom(i))
      if (atom->IsHydrogen())
        delatoms.push_back(atom);

    UnsetHydrogensAdded();

    if (delatoms.empty())
      return(true);


    IncrementMod();


    for (i = delatoms.begin();i != delatoms.end();++i)
      DeleteAtom((OBAtom *)*i);

    DecrementMod();

    UnsetSSSRPerceived();
    return(true);
  }
