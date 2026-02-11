kstrchr(XChar2b *string, XChar2b kchar)
{
	while(string->byte1 !=0){
		if((kchar.byte1==string->byte1) &&
		   (kchar.byte2==string->byte2))
		{
			return string;
		}
		string++;
	}

	return NULL;
}
