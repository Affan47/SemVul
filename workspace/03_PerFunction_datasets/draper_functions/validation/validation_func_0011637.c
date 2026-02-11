sdParseExternalCharset(Sd &sd, UnivCharsetDesc &desc)
{
  SdParam parm;
  for (;;) {
    if (!parseSdParam(AllowedSdParams(SdParam::number, SdParam::eE),
		     parm))
      break;
    if (parm.type == SdParam::eE)
      return 1;
    WideChar min = parm.n;
    if (!parseSdParam(AllowedSdParams(SdParam::number), parm))
      break;
    Number count = parm.n;
    if (!parseSdParam(AllowedSdParams(SdParam::number,
				      SdParam::minimumLiteral,
				      SdParam::reservedName + Sd::rUNUSED),
		     parm))
      break;
    if (parm.type == SdParam::number) {
      if (count > 0)
	desc.addRange(min, min + (count - 1), parm.n);
    }
    else if (parm.type == SdParam::minimumLiteral) {
      UnivChar c = charNameToUniv(sd, parm.literalText.string());
      if (count > 256) {
	message(ParserMessages::tooManyCharsMinimumLiteral);
	count = 256;
      }
      for (Number i = 0; i < count; i++)
	desc.addRange(min + i, min + i, c);
    }
  }
  popInputStack();
  return 0;
}
