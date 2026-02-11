ref2ibm(double *pref, int kbits)
{


  static int itrnd;
  static int kexp, kmant;
  static double ztemp, zdumm;
  extern int CGRIBEX_Debug;


  itrnd = 1;
  zdumm = ztemp = *pref;
  confp3(zdumm, &kexp, &kmant, kbits, itrnd);

  if ( kexp == 0 && kmant == 0 ) return;


  *pref = decfp2(kexp, kmant);


  if ( ztemp < *pref )
    {


      itrnd = 0;
      zdumm = *pref = ztemp;
      confp3(zdumm, &kexp, &kmant, kbits, itrnd);


      *pref = decfp2(kexp, kmant);

      if ( ztemp < *pref )
	{
	  if ( CGRIBEX_Debug )
	    {
	      Message("Reference value error.");
	      Message("Notify Met.Applications Section.");
	      Message("ZTEMP = ", ztemp);
	      Message("PREF = ", pref);
	    }
	  *pref = ztemp;
	}
    }

  return;
}
