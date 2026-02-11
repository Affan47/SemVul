IoSGMLParser_freeParser(IoSGMLParser *self)
{
	if (DATA(self)->isInitialized)
	{
		sgmlParserDestroy(&(DATA(self)->parser), 0);
		DATA(self)->isInitialized = 0;
	}
}
