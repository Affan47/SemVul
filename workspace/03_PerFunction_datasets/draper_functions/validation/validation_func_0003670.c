initChannel(
  vector<HelicityParticle>& p) {

  pID.clear();
  pM.clear();
  for(int i = 0; i < static_cast<int>(p.size()); i++) {
    pID.push_back(p[i].id());
    pM.push_back(p[i].m());
  }
  initConstants();
  return this;

}
