encput(ILubyte byt, ILubyte cnt)
{
	if (cnt) {
		if ((cnt == 1) && (0xC0 != (0xC0 & byt))) {
			if (IL_EOF == iputc(byt))
				return(0);
			return(1);
		}
		else {
			if (IL_EOF == iputc((ILubyte)((ILuint)0xC0 | cnt)))
				return (0);
			if (IL_EOF == iputc(byt))
				return (0);
			return (2);
		}
	}

	return (0);
}
