utest_SymConvert(char *tmpfile)
{
  char         *msg = "SymConvert() unit test failure";
  ESLX_MSAFILE *mfp = NULL;
  ESL_MSA      *msa = NULL;
#ifdef eslAUGMENT_ALPHABET
  ESL_ALPHABET *abc = NULL;
#endif

  if (eslx_msafile_Open(NULL, tmpfile, NULL, eslMSAFILE_STOCKHOLM, NULL, &mfp) != eslOK) esl_fatal(msg);
  if (eslx_msafile_Read(mfp, &msa) != eslOK)                                             esl_fatal(msg);
  eslx_msafile_Close(mfp);


  if (esl_msa_SymConvert(msa, "VWY", "-")          != eslOK) esl_fatal(msg);
  if (esl_msa_MinimGaps(msa, NULL, "-~", FALSE)    != eslOK) esl_fatal(msg);
  if (msa->alen                                    != 39)    esl_fatal(msg);


  if (esl_msa_SymConvert(msa, "DEF", "VWY") != eslOK) esl_fatal(msg);
  if (msa->aseq[0][4]                       != 'V')   esl_fatal(msg);
  if (msa->aseq[0][5]                       != 'W')   esl_fatal(msg);
  if (msa->aseq[0][23]                      != 'Y')   esl_fatal(msg);


#ifdef eslTEST_THROWING
  if (esl_msa_SymConvert(msa, "XXX", "XX")  != eslEINVAL) esl_fatal(msg);
#endif
  esl_msa_Destroy(msa);

#ifdef eslAUGMENT_ALPHABET
  if ((abc = esl_alphabet_Create(eslAMINO)) == NULL) esl_fatal(msg);
  if (eslx_msafile_Open(&abc, tmpfile, NULL, eslMSAFILE_STOCKHOLM, NULL, &mfp) != eslOK) esl_fatal(msg);
  if (eslx_msafile_Read(mfp, &msa) != eslOK) esl_fatal(msg);
  eslx_msafile_Close(mfp);
#ifdef eslTEST_THROWING
  if (esl_msa_SymConvert(msa, "Tt", "Uu") != eslEINVAL) esl_fatal(msg);
#endif
  esl_msa_Destroy(msa);
  esl_alphabet_Destroy(abc);
#endif
  return;
}
