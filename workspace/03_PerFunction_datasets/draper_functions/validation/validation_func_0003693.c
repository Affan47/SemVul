IsSeries(Object o)
{
    if (DXGetObjectClass(o) != CLASS_GROUP)
	return 0;
    if (DXGetGroupClass((Group)o) != CLASS_SERIES)
	return 0;
    return 1;
}
