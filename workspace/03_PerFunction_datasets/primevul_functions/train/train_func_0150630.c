_idn2_bidi (const uint32_t * label, size_t llen)
{
  int bc;
  int endok = 1;

  if (!_isBidi (label, llen))
    return IDN2_OK;


  switch ((bc = uc_bidi_category (*label))) {
    case UC_BIDI_L:

      for (size_t it = 1; it < llen; it++) {
	bc = uc_bidi_category(label[it]);

	if (bc == UC_BIDI_L || bc == UC_BIDI_EN || bc == UC_BIDI_NSM) {
	  endok = 1;
	} else {
	  if (bc != UC_BIDI_ES && bc != UC_BIDI_CS && bc != UC_BIDI_ET && bc != UC_BIDI_ON && bc != UC_BIDI_BN) {

	    return IDN2_BIDI;
	  }
	  endok = 0;
	}
      }

      return endok ? IDN2_OK : IDN2_BIDI;

    case UC_BIDI_R:
    case UC_BIDI_AL:


      for (size_t it = 1; it < llen; it++) {
	bc = uc_bidi_category(label[it]);


	if (bc == UC_BIDI_R || bc == UC_BIDI_AL || bc == UC_BIDI_EN || bc == UC_BIDI_AN || bc == UC_BIDI_NSM) {
	  endok = 1;
	} else {
	  if (bc != UC_BIDI_ES && bc != UC_BIDI_CS && bc != UC_BIDI_ET && bc != UC_BIDI_ON && bc != UC_BIDI_BN) {

	    return IDN2_BIDI;
	  }
	  endok = 0;
	}
      }

      return endok ? IDN2_OK : IDN2_BIDI;

    default:

      return IDN2_BIDI;
  }
}
