init( int iFit, string xmlPath, Info* infoPtr) {


  if (xmlPath[ xmlPath.length() - 1 ] != '/') xmlPath += "/";
  string         dataFile = "pomH1FitBlo.data";
  if (iFit == 1) dataFile = "pomH1FitA.data";
  if (iFit == 2) dataFile = "pomH1FitB.data";
  ifstream is( (xmlPath + dataFile).c_str() );
  if (!is.good()) {
    if (infoPtr != 0) infoPtr->errorMsg("Error from PomH1FitAB::init: "
      "the H1 Pomeron parametrization file was not found");
    else cout << " Error from PomH1FitAB::init: "
      << "the H1 Pomeron parametrization file was not found" << endl;
    isSet = false;
    return;
  }


  nx    = 100;
  xlow  = 0.001;
  xupp  = 0.99;
  dx    = log(xupp / xlow) / (nx - 1.);
  nQ2   = 30;
  Q2low = 1.0;
  Q2upp = 30000.;
  dQ2   = log(Q2upp / Q2low) / (nQ2 - 1.);


  for (int i = 0; i < nx; ++i)
    for (int j = 0; j < nQ2; ++j)
      is >> quarkGrid[i][j];


  for (int i = 0; i < nx; ++i)
    for (int j = 0; j < nQ2; ++j)
      is >> gluonGrid[i][j];


  if (!is) {
    if (infoPtr != 0) infoPtr->errorMsg("Error from PomH1FitAB::init: "
      "the H1 Pomeron parametrization files could not be read");
    else cout << " Error from PomH1FitAB::init: "
      << "the H1 Pomeron parametrization files could not be read" << endl;
    isSet = false;
    return;
  }


  isSet = true;
  return;
}
