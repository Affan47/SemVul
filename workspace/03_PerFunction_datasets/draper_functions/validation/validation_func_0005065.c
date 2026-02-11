gkrellm_destroy_decal(GkrellmDecal *d)
	{
	GkrellmDecalbutton	*b;

	if (d && d->panel)
		{
		if ((b = gkrellm_decal_is_button(d)) != NULL)
			gkrellm_destroy_button(b);
		else
			{
			_remove_decal((GkrellmPanel *) d->panel, d);
			_destroy_decal(d);
			}
		}
	else
		_destroy_decal(d);
	}
