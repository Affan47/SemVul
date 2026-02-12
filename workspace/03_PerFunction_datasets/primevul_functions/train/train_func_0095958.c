static void setOrigString(struct strbufinfo old)
{
	free(dcstr);
	strsize=old.size;
	strmaxsize=old.maxsize;
	dcstr=old.str;
	dcptr=old.ptr;
}
