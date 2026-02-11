getValence() {
    int result=0;
    if (this->tb <=NBONDTYPES) result=bondValence[this->tb-1];
    return result;
  }
