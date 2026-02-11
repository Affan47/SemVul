medianof3(const GtBentsedgresources *bsr,
                               unsigned long subbucketleft,
                               unsigned long depth,
                               unsigned long a,
                               unsigned long b,
                               unsigned long c)
{
  GtSfxcmp vala, valb, valc;
  GtCommonunits commonunits;
  int retvalavalb, retvalavalc, retvalbvalc;

  PTR2INT(vala,subbucketleft,a);
  PTR2INT(valb,subbucketleft,b);
  Sfxdocompare(&commonunits,vala,valb);
  if (GtSfxcmpEQUAL(vala,valb))
  {
    return a;
  }
  PTR2INT(valc,subbucketleft,c);
  Sfxdocompare(&commonunits,vala,valc);
  if (GtSfxcmpEQUAL(vala,valc))
  {
    return c;
  }
  Sfxdocompare(&commonunits,valb,valc);
  if (GtSfxcmpEQUAL(valb,valc))
  {
    return c;
  }
  return GtSfxcmpSMALLER(vala,valb) ?
        (GtSfxcmpSMALLER(valb,valc) ? b : (GtSfxcmpSMALLER(vala,valc) ? c : a))
      : (GtSfxcmpGREATER(valb,valc) ? b : (GtSfxcmpSMALLER(vala,valc) ? a : c));
}
