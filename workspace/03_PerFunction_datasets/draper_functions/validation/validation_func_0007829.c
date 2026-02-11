s_getMirrorChar(UT_UCSChar c)
{

	UT_UCS4Char mc;

	if (UT_bidiGetMirrorChar(c,mc))
		return mc;
	else
		return c;
}
