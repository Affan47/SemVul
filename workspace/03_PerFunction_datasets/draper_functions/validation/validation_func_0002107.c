initProc() {


  nameSave = "gamma gamma -> f fbar";
  if (idNew ==  1) nameSave = "gamma gamma -> q qbar (uds)";
  if (idNew ==  4) nameSave = "gamma gamma -> c cbar";
  if (idNew ==  5) nameSave = "gamma gamma -> b bbar";
  if (idNew ==  6) nameSave = "gamma gamma -> t tbar";
  if (idNew == 11) nameSave = "gamma gamma -> e+ e-";
  if (idNew == 13) nameSave = "gamma gamma -> mu+ mu-";
  if (idNew == 15) nameSave = "gamma gamma -> tau+ tau-";


  idMass = 0;
  if (idNew > 3) idMass = idNew;


  ef4 = 1.;
  if (idNew == 1) ef4 = 3. * (pow4(2./3.) + 2. * pow4(1./3.));
  if (idNew == 4 || idNew == 6) ef4 = 3. * pow4(2./3.);
  if (idNew == 5) ef4 = 3. * pow4(1./3.);


  openFracPair = particleDataPtr->resOpenFrac(idNew, -idNew);

}
