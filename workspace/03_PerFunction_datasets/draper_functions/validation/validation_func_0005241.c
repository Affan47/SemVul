destroyZlmTable()
{
	gint l;
	if(z)
	{
		for(l=0;l<=z->lMax;l++) if(z->data[l]) g_free(z->data[l]);
		if(z->data) g_free(z->data);
	}
	z = NULL;
}
