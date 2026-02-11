pms_initdfsconstinfo(Limdfsconstinfo *mt,
                                 unsigned int alphasize,
                                 ...)


{
  va_list ap;
  GtMssufpatLimdfsconstinfo *mti = (GtMssufpatLimdfsconstinfo*) mt;
  const GtUchar *pattern;

  va_start(ap,alphasize);
  pattern = va_arg(ap, const GtUchar *);
  mti->patternlength = va_arg(ap, unsigned long);
  va_end(ap);
  gt_initeqsvector(mti->eqsvector,(unsigned long) alphasize,
                pattern,mti->patternlength);
}
