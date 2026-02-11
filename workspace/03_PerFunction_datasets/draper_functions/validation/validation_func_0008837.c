compute_print_cov(FILE* outputFile, Options userOpt, int* data, char* name,const uint32_t chrSize, int64_t* coverageHist,const int currentTid)
{
  int32_t covVal = 0;
  int64_t covSum = 0;
  int32_t i;


  for (i=0; i<chrSize; ++i){
    covVal += data[i];


    data[i] = covVal;
    covSum += covVal;

    if (covVal > userOpt.maxCoverage) {
      ++coverageHist[userOpt.maxCoverage];
    } else {
      ++coverageHist[covVal];
    }

  }
  if (userOpt.doMedian)

    radix_sort(data, chrSize);


  printf("Average coverage over %s : %3.2f\n", name, (double)covSum / chrSize);
  if (userOpt.doMedian)
    printf("Median coverage over %s : %d\n", name, data[chrSize/2]);
  if (userOpt.printAll == 1) {
    if (userOpt.doMedian)
      fprintf(outputFile, "%s\t%d\t%3.5f\t%d\n", name, chrSize, (double)covSum / chrSize, data[chrSize/2]);
    else
      fprintf(outputFile, "%s\t%d\t%3.5f\n", name, chrSize, (double)covSum / chrSize);
  } else if (currentTid < 24) {


    if (userOpt.doMedian)
      fprintf(outputFile, "%s\t%d\t%3.5f\t%d\n", name, chrSize, (double)covSum / chrSize, data[chrSize/2]);
    else
      fprintf(outputFile, "%s\t%d\t%3.5f\n", name, chrSize, (double)covSum / chrSize);
  }
}
