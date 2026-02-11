ISSTEP2(gribProduct ** grib, fortint * timeStepP2) {
gribProduct * g = *grib;
fortint zero = 0;

  if( DEBUG1 ) printf("ISSTEP2: timeStepP2 = %d\n",*timeStepP2);

  switch( (int) g1_timerange(g) ) {

    case 0:
    case 1:
      MOVE1BYTE(((g->g1)->P2),&zero);
      return 0;

    case 2:
    case 3:
    case 4:
    case 5:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 123:
    case 124:
      MOVE1BYTE(((g->g1)->P2),timeStepP2);
      return 0;

    case 10:
      printf("ISSTEP2: unable to set P2 for time range indicator %d\n", g1_timerange(g));
      return -1;

    default:
      printf("ISSTEP2: unable to set P2 for reserved time range indicator %d\n", g1_timerange(g));
      return -1;
  }

}
