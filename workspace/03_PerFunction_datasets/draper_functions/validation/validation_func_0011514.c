checkShortrefDelim(const Syntax &syn,
				   const CharsetInfo &charset,
				   const StringC &delim)
{
  Boolean hadB = 0;
  Char letterB = charset.execToDesc('B');
  const ISet<Char> *bSet = syn.charSet(Syntax::blank);
  for (size_t i = 0; i < delim.size(); i++)
    if (delim[i] == letterB) {
      if (hadB) {
	message(ParserMessages::multipleBSequence, StringMessageArg(delim));
	return 0;
      }
      hadB = 1;
      if (i > 0 && bSet->contains(delim[i - 1])) {
	message(ParserMessages::blankAdjacentBSequence,
		StringMessageArg(delim));
	return 0;
      }
      while (i + 1 < delim.size() && delim[i + 1] == letterB)
	i++;
      if (i < delim.size() - 1 && bSet->contains(delim[i + 1])) {
	message(ParserMessages::blankAdjacentBSequence,
		StringMessageArg(delim));
	return 0;
      }
    }
  return 1;
}
