load(const MEMORY_HANDLE h,long len)
{
	handle=TKawariShioriFactory::GetFactory().CreateInstance(
		string((const char*)h, len));
	SHIORI_FREE(h);
	return (handle!=0);
}
