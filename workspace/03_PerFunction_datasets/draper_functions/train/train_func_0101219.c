IoFile_atPut(IoFile *self, IoObject *locals, IoMessage *m)
{


	int c = IoMessage_locals_intArgAt_(m, locals, 1);

	IoFile_assertOpen(self, locals, m);
	IoFile_assertWrite(self, locals, m);
	IoFile_position_(self, locals, m);

	if (fputc(c, DATA(self)->stream) == EOF)
	{
		int pos = IoMessage_locals_intArgAt_(m, locals, 0);
		IoState_error_(IOSTATE, m, "error writing to position %i in file '%s'", pos, CSTRING(DATA(self)->path));
	}

	return self;
}
