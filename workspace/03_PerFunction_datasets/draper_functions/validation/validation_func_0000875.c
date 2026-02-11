TypeToString(const Type type)
{
    ListIterator iterator(*DXType::TypeList);
    DXTypeName*  knownType;


    while ((knownType=(DXTypeName*)iterator.getNext()))
    {
	if (type == knownType->type)
	{
	    return knownType->name;
	}
    }

    return NUL(const char*);
}
