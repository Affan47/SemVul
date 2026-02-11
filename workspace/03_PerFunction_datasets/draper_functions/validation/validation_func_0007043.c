emit_byte(int i)
{
	if (pass>0)
		{
			fputc(i,fo);
			if (indata) datasize++;
		}
	offset++;
	codesize++;
}
