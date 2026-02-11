esl_msafile_psiblast_SetInmap(ESLX_MSAFILE *afp)
{
   int sym;

#ifdef eslAUGMENT_ALPHABET
  if (afp->abc)
    {
      for (sym = 0; sym < 128; sym++)
	afp->inmap[sym] = afp->abc->inmap[sym];
      afp->inmap[0]   = esl_abc_XGetUnknown(afp->abc);
      afp->inmap['.'] = eslDSQ_ILLEGAL;
      afp->inmap['_'] = eslDSQ_ILLEGAL;
      afp->inmap['*'] = eslDSQ_ILLEGAL;
      afp->inmap['~'] = eslDSQ_ILLEGAL;
    }
#endif
  if (! afp->abc)
    {
      for (sym = 1; sym < 128; sym++)
	afp->inmap[sym] = (isalpha(sym) ? sym : eslDSQ_ILLEGAL);
      afp->inmap[0]   = '?';
      afp->inmap['-'] = '-';
    }

  afp->inmap['O'] = eslDSQ_ILLEGAL;
  afp->inmap['o'] = eslDSQ_ILLEGAL;
  return eslOK;
}
