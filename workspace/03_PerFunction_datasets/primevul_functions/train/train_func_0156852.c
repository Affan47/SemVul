datetime_to_char_body(TmToChar *tmtc, text *fmt, bool is_interval, Oid collid)
{
	FormatNode *format;
	char	   *fmt_str,
			   *result;
	bool		incache;
	int			fmt_len;
	text	   *res;


	fmt_str = text_to_cstring(fmt);
	fmt_len = strlen(fmt_str);


	result = palloc((fmt_len * DCH_MAX_ITEM_SIZ) + 1);
	*result = '\0';


	if (fmt_len > DCH_CACHE_SIZE)
	{
		format = (FormatNode *) palloc((fmt_len + 1) * sizeof(FormatNode));
		incache = FALSE;

		parse_format(format, fmt_str, DCH_keywords,
					 DCH_suff, DCH_index, DCH_TYPE, NULL);

		(format + fmt_len)->type = NODE_TYPE_END;
	}
	else
	{


		DCHCacheEntry *ent;

		incache = TRUE;

		if ((ent = DCH_cache_search(fmt_str)) == NULL)
		{
			ent = DCH_cache_getnew(fmt_str);


			parse_format(ent->format, fmt_str, DCH_keywords,
						 DCH_suff, DCH_index, DCH_TYPE, NULL);

			(ent->format + fmt_len)->type = NODE_TYPE_END;

#ifdef DEBUG_TO_FROM_CHAR


#endif
		}
		format = ent->format;
	}


	DCH_to_char(format, is_interval, tmtc, result, collid);

	if (!incache)
		pfree(format);

	pfree(fmt_str);


	res = cstring_to_text(result);

	pfree(result);
	return res;
}
