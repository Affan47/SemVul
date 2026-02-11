index_subsys_index_matches_associated(indexEntry *index, Slapi_Filter *f)
{
	int ret = 0;
	char **associated_attrs = index->associated_attrs;

	if(INDEX_MATCH_NONE != index_subsys_index_matches_filter(index, f))
	{

		ret = -1;
		goto bail;
	}


	if(associated_attrs)
	{
		int i;
		char *type = f->f_type;

		for(i=0; associated_attrs[i]; i++)
		{
			if(slapi_attr_types_equivalent(associated_attrs[i], type))
			{

				ret = -1;
				break;
			}
		}
	}

bail:
	return ret;
}
