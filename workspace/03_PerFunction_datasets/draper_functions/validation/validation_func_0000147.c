amdmsAnalyzePE(amdmsPARTICLE_EVENT_SETUP *setup, int iPE, amdmsPIXEL var)
{
  int              iPixel;
  int              start, split, end;
  amdmsPIXEL        mean1, var1;
  amdmsPIXEL        mean2, var2;

  iPixel = setup->pes[iPE].idx;
  start = 0;
  end = setup->nValues;
  split = end/2;


  amdmsCalcMeanVar(setup, iPE, start, split, &mean1, &var1);
  amdmsCalcMeanVar(setup, iPE, split, end, &mean2, &var2);
  if ((var1 < amdmsLOWER_PE*var) && (var2 > amdmsUPPER_PE*var)) {


    split -= 20;
    amdmsCalcMeanVar(setup, iPE, start, split, &mean1, &var1);
    amdmsCalcMeanVar(setup, iPE, split, end, &mean2, &var2);
    if ((var1 < amdmsLOWER_PE*var) && (var2 > amdmsUPPER_PE*var)) {


      setup->pes[iPE].start = split;
      setup->pes[iPE].end = end;
      setup->pes[iPE].mean = mean1;
      setup->pes[iPE].var = var1;
    } else {

      setup->pes[iPE].isBad = amdmsTRUE;
    }
  } else if ((var1 > amdmsUPPER_PE*var) && (var2 < amdmsLOWER_PE*var)) {


    split += 20;
    amdmsCalcMeanVar(setup, iPE, start, split, &mean1, &var1);
    amdmsCalcMeanVar(setup, iPE, split, end, &mean2, &var2);
    if ((var1 > amdmsUPPER_PE*var) && (var2 < amdmsLOWER_PE*var)) {


      setup->pes[iPE].start = start;
      setup->pes[iPE].end = split;
      setup->pes[iPE].mean = mean2;
      setup->pes[iPE].var = var1;
    } else {

      setup->pes[iPE].isBad = amdmsTRUE;
    }
  } else {
    setup->pes[iPE].isBad = amdmsTRUE;
  }
  if (setup->pes[iPE].isBad) {
    amdmsDebug(__FILE__, __LINE__,
	      "no PE at pixel(%d, %d): mean = (%.4g | %.4g), var = (%.4g | %.4g | %.4g)",
	      setup->pes[iPE].x, setup->pes[iPE].y, mean1, mean2, var1, var, var2);
  } else {
    amdmsDebug(__FILE__, __LINE__,
	      "possible PE at pixel(%d, %d): mean = (%.4g | %.4g), var = (%.4g > %.4g > %.4g)",
	      setup->pes[iPE].x, setup->pes[iPE].y, mean1, mean2, var1, var, var2);
  }
}
