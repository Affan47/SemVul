get_symb_type_charge(gchar* str,gchar symb[], gchar type[], gchar charge[])
{
	gint i;
	gchar** split = g_strsplit(str,"-",4);

	sprintf(symb,"H");
	sprintf(type,"H");
	sprintf(charge,"0.0");
	if(!str)
		return;
	sprintf(symb,"%s",str);
	sprintf(type,"%s",str);
	if(split)
	for(i=0;i<4;i++)
	{
		if(!split[i])
			break;

		switch(i)
		{
			case 0: sprintf(symb,"%s",split[0]);
				g_free(split[0]);
				break;
			case 1: sprintf(type,"%s",split[1]);
				g_free(split[1]);
				break;
			case 2: if(strlen(split[2])<1)
				{
					g_free(split[2]);
					break;
				}
				sprintf(charge,"%s",split[2]);
				g_free(split[2]);
				break;
			case 3: sprintf(charge,"-%s",split[3]);
				g_free(split[3]);
		}
	}
}
