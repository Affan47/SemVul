decayOctetOnia(Event& event) {


  int idOnium[6] = { 9900443, 9900441, 9910441,
                     9900553, 9900551, 9910551 };


  for (int iDec = 0; iDec < event.size(); ++iDec)
  if (event[iDec].isFinal()) {
    int id = event[iDec].id();
    bool isOnium = false;
    for (int j = 0; j < 6; ++j) if (id == idOnium[j]) isOnium = true;


    if (isOnium) {
      if (!decays.decay( iDec, event)) return false;


      int iGlu = event.size() - 1;
      event[iGlu].cols( event[iDec].col(), event[iDec].acol() );
    }
  }


  return true;

}
