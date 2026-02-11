amdmsCreatePhotonTransferCurveMap(amdmsALGO_PROPERTIES_ENV *env,
					   amdmsFITS *outfile,
					   amdmsFITS_FLAGS flags)
{
  int     i;

  if (amdmsCreateData(outfile, flags, amdmsPTC_NROWS, 1) != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  for (i = 0; i < amdmsPTC_NROWS; i++) {
    env->ptcFit[i].index = (double)(i + 1);
    if (amdmsWriteData(outfile, &(env->ptcFit[i]), i, 0) != amdmsSUCCESS) {
      return amdmsFAILURE;
    }
  }
  return amdmsSUCCESS;
}
