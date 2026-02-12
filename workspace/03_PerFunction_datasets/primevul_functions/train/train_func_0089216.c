lookup_cset(ushort nrc_code, uchar csmask, bool enabled)
{
  static struct {
    ushort design;
    uchar cstype;
    bool free;
    uchar cs;
  } csdesignations[] = {
    {'B', 1, 1, CSET_ASCII},
    {'A', 3, 1, CSET_GBCHR},
    {'0', 1, 1, CSET_LINEDRW},
    {'>', 1, 1, CSET_TECH},
    {'U', 1, 1, CSET_OEM},
    {'<', 1, 1, CSET_DECSUPP},
    {CPAIR('%', '5'), 1, 1, CSET_DECSPGR},

    {'4', 1, 0, CSET_NL},
    {'C', 1, 0, CSET_FI},
    {'5', 1, 0, CSET_FI},
    {'R', 1, 0, CSET_FR},
    {'f', 1, 0, CSET_FR},
    {'Q', 1, 0, CSET_CA},
    {'9', 1, 0, CSET_CA},
    {'K', 1, 0, CSET_DE},
    {'Y', 1, 0, CSET_IT},
    {'`', 1, 0, CSET_NO},
    {'E', 1, 0, CSET_NO},
    {'6', 1, 0, CSET_NO},
    {CPAIR('%', '6'), 1, 0, CSET_PT},
    {'Z', 1, 0, CSET_ES},
    {'H', 1, 0, CSET_SE},
    {'7', 1, 0, CSET_SE},
    {'=', 1, 0, CSET_CH},

    {'L', 2, 1, CSET_ISO_Latin_Cyrillic},
    {'F', 2, 1, CSET_ISO_Greek_Supp},
    {'H', 2, 1, CSET_ISO_Hebrew},
    {'M', 2, 1, CSET_ISO_Latin_5},
    {CPAIR('"', '?'), 1, 1, CSET_DEC_Greek_Supp},
    {CPAIR('"', '4'), 1, 1, CSET_DEC_Hebrew_Supp},
    {CPAIR('%', '0'), 1, 1, CSET_DEC_Turkish_Supp},
    {CPAIR('&', '4'), 1, 1, CSET_DEC_Cyrillic},
    {CPAIR('"', '>'), 1, 0, CSET_NRCS_Greek},
    {CPAIR('%', '='), 1, 0, CSET_NRCS_Hebrew},
    {CPAIR('%', '2'), 1, 0, CSET_NRCS_Turkish},
  };
  for (uint i = 0; i < lengthof(csdesignations); i++)
    if (csdesignations[i].design == nrc_code
        && (csdesignations[i].cstype & csmask)
        && (csdesignations[i].free || enabled)
       )
    {
      return csdesignations[i].cs;
    }
  return 0;
}
