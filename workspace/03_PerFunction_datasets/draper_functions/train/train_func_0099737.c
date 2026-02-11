get_string_all_children(gint row)
{
	gint Numb = 0;
	gint *NumChildren = NULL;
	gint j;
  	gchar* rowprocess = NULL;
  	gchar* str = NULL;
  	gchar* dump = NULL;

	NumChildren = get_all_children(row,&Numb);
	if(Numb>0)
  		str = get_title_process();

 	for(j=0;j<Numb;j++)
 	{
  		rowprocess = get_row_process(NumChildren[j]);
		dump = str;
		if(j==0)
  			str = g_strdup_printf("%s%s",dump,rowprocess);
		else
  			str = g_strdup_printf("%s\n%s",dump,rowprocess);
		g_free(dump);
		if(rowprocess)
		{
			g_free(rowprocess);
			rowprocess = NULL;
		}
 	}
	if(NumChildren)
		g_free(NumChildren);
	return str;

}
