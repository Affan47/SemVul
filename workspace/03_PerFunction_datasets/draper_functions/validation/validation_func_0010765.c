unregc()
{
	if (regcode != &regdummy)
#ifdef KANJI
	{
		if (ISkanji(* --regcode))
			regcode--;
	}
#else
		regcode--;
#endif
	else
		regsize--;
}
