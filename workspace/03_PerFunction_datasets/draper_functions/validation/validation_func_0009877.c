weight_UNLOPS_SUBTNLO(PartonLevel* trial, double RN ) {


  History *  selected = select(RN);

  selected->setScalesInHistory();

  double wt = 1.;

  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightTreeEmissions( trial, -1, njetsMaxMPI,
                   maxScale );
  wt = mpiwt;

  return wt;

}
