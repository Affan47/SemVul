_e2_fileview_compile_filter_patterns (ViewInfo *view)
{
	if (view->name_filter.compiled_patterns != NULL)
		_e2_fileview_clear_filter_patterns (view);

	E2_SelectPattern *patterninfo;
	GSList *members = NULL;
	gchar *s, *p, *freeme;
	gchar save;

	p = view->name_filter.patternptr;

	while ((s = strchr (p, ',')) != NULL)
	{
		while (p[0] == ' ')
			p++;
		if (p == s)
		{
			p++;
			continue;
		}
		patterninfo = MALLOCATE (E2_SelectPattern);
		CHECKALLOCATEDWARN (patterninfo, )
		if (patterninfo == NULL)
		{
			g_slist_free (members);
			return FALSE;
		}
		members = g_slist_append (members, patterninfo);
		if (p[0] == '!')
		{
			patterninfo->negated = !view->name_filter.invert_mask;
			p++;
		}
		else
		{
			patterninfo->negated = view->name_filter.invert_mask;
			if (p[0] == '\\' && p[1] == '!')
				p++;
		}

		save = *s;
		*s = '\0';

		if (!view->name_filter.case_sensitive)
		{
			freeme = g_utf8_strdown (p, -1);
			patterninfo->pspec = g_pattern_spec_new (freeme);
			g_free (freeme);
		}
		else
			patterninfo->pspec = g_pattern_spec_new (p);

		*s = save;
		NCHR(s);
		p = s;
	}

	while (p[0] == ' ')
		p++;
	if (p[0] == '\0')
	{
		view->name_filter.compiled_patterns = members;
		return (members != NULL);
	}

	patterninfo = MALLOCATE (E2_SelectPattern);
	CHECKALLOCATEDWARN (patterninfo, )
	if (patterninfo == NULL)
	{
		g_slist_free (members);
		return FALSE;
	}
	members = g_slist_append (members, patterninfo);

	if (p[0] == '!')
	{
		patterninfo->negated = !view->name_filter.invert_mask;
		p++;
	}
	else
	{
		patterninfo->negated = view->name_filter.invert_mask;
		if (p[0] == '\\' && p[1] == '!')
			p++;
	}
	if (!view->name_filter.case_sensitive)
	{
		freeme = g_utf8_strdown (p, -1);
		patterninfo->pspec = g_pattern_spec_new (freeme);
		g_free (freeme);
	}
	else
		patterninfo->pspec = g_pattern_spec_new (p);

	view->name_filter.compiled_patterns = members;
	return TRUE;
}
