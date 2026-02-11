VarHead(const char *word, Boolean addSpace, Buffer *buf, void *dummy __unused)
{
	char *slash;

	slash = strrchr(word, '/');
	if (slash != NULL) {
		if (addSpace) {
			Buf_AddByte(buf, (Byte)' ');
		}
		Buf_AppendRange(buf, word, slash);
	} else {


		if (addSpace) {
			Buf_Append(buf, " .");
		} else {
			Buf_AddByte(buf, (Byte)'.');
		}
	}
	return (TRUE);
}
