escape(const char *aSpecialChars, bool bit7)
{
	if (!mLength) return;
	String copy(this);
	realloc(mLength*4);
	realloc(escape_special((char*)mContent, mLength+1, copy.mContent,
					   copy.mLength, aSpecialChars, bit7));
}
