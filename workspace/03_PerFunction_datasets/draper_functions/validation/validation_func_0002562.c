getEntry(int i)
{
  if (entries[i].type == xrefEntryNone) {

    if ((!xRefStream) && mainXRefEntriesOffset) {
      if (!parseEntry(mainXRefEntriesOffset + 20*i, &entries[i])) {
        error(-1, "Failed to parse XRef entry [%d].", i);
      }
    } else {
      std::vector<Guint> followedPrev;
      while (prevXRefOffset && entries[i].type == xrefEntryNone) {
        bool followed = false;
        for (size_t j = 0; j < followedPrev.size(); j++) {
          if (followedPrev.at(j) == prevXRefOffset) {
            followed = true;
            break;
          }
        }
        if (followed) {
          error(-1, "Circular XRef");
          if (!(ok = constructXRef(NULL))) {
            errCode = errDamaged;
          }
          break;
        }

        followedPrev.push_back (prevXRefOffset);

        std::vector<Guint> followedXRefStm;
        if (!readXRef(&prevXRefOffset, &followedXRefStm)) {
            prevXRefOffset = 0;
        }


        if (!ok) {
           GBool wasReconstructed = false;
           if (!(ok = constructXRef(&wasReconstructed))) {
               errCode = errDamaged;
               break;
           }
           break;
        }
      }

      if (entries[i].type == xrefEntryNone) {
         error(-1, "Invalid XRef entry");
         entries[i].type = xrefEntryFree;
      }
    }
  }

  return &entries[i];
}
