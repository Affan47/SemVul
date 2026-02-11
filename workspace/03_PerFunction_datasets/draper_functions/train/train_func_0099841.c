db_find_property(Objid oid, const char *name, Var * value)
{
    static struct {
	const char *name;
	enum bi_prop prop;
	int hash;
    } ptable[] = {
	{
	    "name", BP_NAME, 0
	},
	{
	    "owner", BP_OWNER, 0
	},
	{
	    "programmer", BP_PROGRAMMER, 0
	},
	{
	    "wizard", BP_WIZARD, 0
	},
	{
	    "r", BP_R, 0
	},
	{
	    "w", BP_W, 0
	},
	{
	    "f", BP_F, 0
	},
	{
	    "location", BP_LOCATION, 0
	},
	{
	    "contents", BP_CONTENTS, 0
	}
    };
    static int ptable_init = 0;
    int i, n;
    db_prop_handle h;
    int hash = str_hash(name);
    Object *o;

    if (!ptable_init) {
	for (i = 0; i < Arraysize(ptable); i++)
	    ptable[i].hash = str_hash(ptable[i].name);
	ptable_init = 1;
    }
    for (i = 0; i < Arraysize(ptable); i++) {
	if (ptable[i].hash == hash && !mystrcasecmp(name, ptable[i].name)) {
	    static Objid ret;

	    ret = oid;
	    h.built_in = ptable[i].prop;
	    h.definer = NOTHING;
	    h.ptr = &ret;
	    if (value)
		get_bi_value(h, value);
	    return h;
	}
    }

    h.built_in = BP_NONE;
    n = 0;
    for (o = dbpriv_find_object(oid); o; o = dbpriv_find_object(o->parent)) {
	Proplist *props = &(o->propdefs);
	Propdef *defs = props->l;
	int length = props->cur_length;

	for (i = 0; i < length; i++, n++) {
	    if (defs[i].hash == hash
		&& !mystrcasecmp(defs[i].name, name)) {
		Pval *prop;

		h.definer = o->id;
		o = dbpriv_find_object(oid);
		prop = h.ptr = o->propval + n;

		if (value) {
		    while (prop->var.type == TYPE_CLEAR) {
			n -= o->propdefs.cur_length;
			o = dbpriv_find_object(o->parent);
			prop = o->propval + n;
		    }
		    *value = prop->var;
		}
		return h;
	    }
	}
    }

    h.ptr = 0;
    return h;
}
