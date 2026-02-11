sed1330_close(Driver * drvthis)
{
	PrivateData *p = drvthis->private_data;

	debug(RPT_DEBUG, "%s()", __FUNCTION__);

	if (p != NULL) {
		int i, j;

		for (i = 0; i < KEYPAD_MAXX; i++) {
			if (p->keyMapDirect[i] != NULL)
				free(p->keyMapDirect[i]);
			for (j = 0; j < KEYPAD_MAXY; j++) {
				if (p->keyMapMatrix[i][j] != NULL)
					free(p->keyMapMatrix[i][j]);
			}
		}

		if (p->framebuf_text != NULL)
			free(p->framebuf_text);
		if (p->lcd_contents_text != NULL)
			free(p->lcd_contents_text);
		if (p->framebuf_graph != NULL)
			free(p->framebuf_graph);
		if (p->lcd_contents_graph != NULL)
			free(p->lcd_contents_graph);

		free(p);
	}
	drvthis->store_private_ptr(drvthis, NULL);
}
