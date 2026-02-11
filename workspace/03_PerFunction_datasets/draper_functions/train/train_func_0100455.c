InternalIsLeadByte(char ch) {
	if (SC_CP_UTF8 == codePage)


		return false;
	else
		return Platform::IsDBCSLeadByte(codePage, ch);
}
