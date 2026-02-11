create_aligner(ElementT *e, RouterT *, ErrorHandler *errh)
{
  int offset, modulus;
  ContextErrorHandler cerrh(errh, "While analyzing alignment for %<%s%>:", e->declaration().c_str());
  if (cp_va_kparse(e->configuration(), &cerrh,
		   "MODULUS", cpkP+cpkM, cpUnsigned, &modulus,
		   "OFFSET", cpkP+cpkM, cpUnsigned, &offset,
		   cpEnd) < 0)
    return default_aligner();
  return new GeneratorAligner(Alignment(modulus, offset));
}
