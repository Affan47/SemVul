SetInternalCoord(std::vector<OBInternalCoord*> int_coord) {
    if (int_coord[0] != NULL) {
      std::vector<OBInternalCoord*>::iterator it = int_coord.begin();
      int_coord.insert(it, static_cast<OBInternalCoord*>(NULL));
    }

    if (int_coord.size() != _natoms + 1) {
      string error = "Number of internal coordinates is not the same as";
      error += " the number of atoms in molecule";
      obErrorLog.ThrowError(__FUNCTION__, error, obError);
      return;
    }

    _internals = int_coord;

    return;
  }
