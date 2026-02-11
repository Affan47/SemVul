terminator(vector<const PseudoJet *> & jets) const {


    if (applies_jet_by_jet()){
      SelectorWorker::terminator(jets);
      return;
    }


    vector<const PseudoJet *> s1_jets = jets;
    _s1.worker()->terminator(s1_jets);


    _s2.worker()->terminator(jets);


    for (unsigned int i=0; i<jets.size(); i++){
      if (! s1_jets[i]) jets[i] = NULL;
    }
  }
