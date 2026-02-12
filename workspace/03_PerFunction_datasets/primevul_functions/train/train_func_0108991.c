pevent_check_all_loaded (void)
{
	int i;

	for (i = 0; i < NUM_XP; i++)
	{
		if (pntevts_text[i] == NULL)
		{


			if (te[i].num_args & 128)
				pntevts_text[i] = g_strdup (te[i].def);
			else
				pntevts_text[i] = g_strdup (_(te[i].def));
		}
	}
}
