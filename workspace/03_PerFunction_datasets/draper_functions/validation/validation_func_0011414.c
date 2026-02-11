db_find_indexed_verb(Objid oid, unsigned index)
{
    Object *o = dbpriv_find_object(oid);
    Verbdef *v;
    unsigned i;
    static handle h;
    db_verb_handle vh;

    for (v = o->verbdefs, i = 0; v; v = v->next)
	if (++i == index) {
	    h.definer = o->id;
	    h.verbdef = v;
	    vh.ptr = &h;

	    return vh;
	}
    vh.ptr = 0;

    return vh;
}
