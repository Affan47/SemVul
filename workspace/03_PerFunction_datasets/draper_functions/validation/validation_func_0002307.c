getOtherVar(int ind){

  if (((degrees[3*ind] != 0) && (degrees[3*ind+2] != 0)) || ((degrees[3*ind] == 0) && (degrees[3*ind+2] == 0)))
    return -2;
  else
    if (degrees[3*ind] == 0)
      return ind+1;
    else
      return ind-1;
}
