get_light_position(gint num)
{
	gint i;
	gchar** t = g_malloc(3*sizeof(gchar*));
	switch(num)
	{
		case 0 :
			for(i=0;i<3;i++)
				 t[i] = g_strdup_printf("%lf",light0_position[i]);
			 break;
		case 1 :
			for(i=0;i<3;i++)
				 t[i] = g_strdup_printf("%lf",light1_position[i]);
			 break;
		case 2 :
			for(i=0;i<3;i++)
				 t[i] = g_strdup_printf("%lf",light2_position[i]);
			 break;
	}
	return t;
}
