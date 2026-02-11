InsertFigureAsComment(const char *s, int hinline)
{
	if (!s) return;
	if (*s=='\0') return;

  if (hinline == 1) fprintRTF("{\\dn10 ");
		putRtfStrEscaped("[###");
		putRtfStrEscaped(s);
		putRtfStrEscaped("###]");
  if (hinline == 1) fprintRTF("}");
}
