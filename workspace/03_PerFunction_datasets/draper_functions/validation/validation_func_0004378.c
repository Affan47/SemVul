DecrementReadOffset(unsigned length)
{
	if (length>readOffset)
		readOffset=lengthAllocated-(length-readOffset);
	else
		readOffset-=length;
}
