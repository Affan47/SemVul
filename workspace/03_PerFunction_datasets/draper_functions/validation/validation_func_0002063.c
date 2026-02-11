exciteTerhardt(double **filterBankOutput, int sampleCount){
  max=-MAXDOUBLE;

  factor=fabs(bankCount-F2CB((double)fs/2.0));


  for (int i=0;i<bankCount;i++){


    excitation[i]=0.0;
    for (int j=0;j<sampleCount;j++){
      excitation[i]+=filterBankOutput[i][j];
    }
    excitation[i]=10.0*log10(excitation[i]);
    if (sampleCount!=fs){


    }
  }


  MooreSpread::excite(filterBankOutput, fs, fs);


  for (int i=0;i<bankCount;i++){
    for (int j=0;j<bankCount;j++)
      Lvmu[j+i*bankCount]=excitation[j]+10.0*log10(spread[i][j]);
  }


  for (int i=0;i<bankCount;i++){
    mask[i]=0.0;
    for (int j=0;j<i;j++)
      mask[i]+=pow(10.0,Lvmu[i+j*bankCount]/20.0);
    for (int j=i+1;j<bankCount;j++)
      mask[i]+=pow(10.0,Lvmu[i+j*bankCount]/20.0);
    mask[i]/=factor;
    if (mask[i]>max) max=mask[i];

  }
}
