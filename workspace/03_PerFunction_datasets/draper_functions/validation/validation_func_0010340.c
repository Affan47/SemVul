FslGetEnvOutputType(void)
{

  char *otype;
  if (FslOverrideOutputType>=0)  return FslOverrideOutputType;
  otype = getenv("FSLOUTPUTTYPE");
  if (otype == NULL) {
    fprintf(stderr,"ERROR:: Environment variable FSLOUTPUTTYPE is not set!\n");
    fprintf(stderr,"Please make sure that the appropriate configuration file is sourced by your shell (e.g. by putting it in .profile).\n");
    fprintf(stderr,"e.g. bash or sh users add the line \". ${FSLDIR}/etc/fslconf/fsl.sh\"\n");
    fprintf(stderr,"e.g. tcsh or csh users add the line \"source ${FSLDIR}/etc/fslconf/fsl.csh\"\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(otype,"NIFTI")==0) { return FSL_TYPE_NIFTI; }
  if (strcmp(otype,"NIFTI_GZ")==0) { return FSL_TYPE_NIFTI_GZ; }
  if (strcmp(otype,"NIFTI_PAIR")==0) { return FSL_TYPE_NIFTI_PAIR; }
  if (strcmp(otype,"NIFTI_PAIR_GZ")==0) { return FSL_TYPE_NIFTI_PAIR_GZ; }
  fprintf(stderr,"ERROR:: Unrecognised value (%s) of environment variable FSLOUTPUTTYPE\n",otype);
  fprintf(stderr,"Legal values are: NIFTI, NIFTI_PAIR, NIFTI_GZ, NIFTI_PAIR_GZ\n");
  exit(EXIT_FAILURE);
  return -1;
}
