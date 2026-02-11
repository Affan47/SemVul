clunit_get_unit_type_index(cst_clunit_db *cludb, const char *name)
{
    int start,end,mid,c;

    start = 0;
    end = cludb->num_types;

    while (start < end)
    {
	mid = (start+end)/2;
	c = strcmp(cludb->types[mid].name,name);

	if (c == 0)
	    return mid;
	else if (c > 0)
	    end = mid;
	else
	    start = mid + 1;
    }

    cst_errmsg("clunits: unit type \"%s\" not found\n",name);
    return -1;
}
