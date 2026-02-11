stringAction(const char *b, const char *e)
	{
		parseStack.pushBack(new (allocator)StringNode(b, e, allocator));
	}
