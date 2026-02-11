_string(char *s, int add, int object)
{
    char *t, *ss;
    int h, c;
    struct hash *hash;


    if (!table)
	DXinitdx();
    if (!table)
	return 0;
    hash = table->hash;


    for (ss=s, h=0; (c=(unsigned char)*ss)!=0; ss++)
	h = WRAP(17*h + c);


    for (h=h; (t=hash[h].s)!=0; h=WRAP(h+1))
	if (strcmp(t,s)==0)
	    break;


    if (!t && add) {
	DXlock(&table->DXlock, 0);
	for (h=h; (t=hash[h].s)!=0; h=WRAP(h+1))
	    if (strcmp(t,s)==0)
		break;
	if (!t) {
	    Object o = (Object) DXNewString(s);
	    _dxf_SetPermanent(o);
	    if (o) {
		t = DXGetString((String)o);
		hash[h].o = o;
		hash[h].s = t;
	    }
	}
	DXunlock(&table->DXlock, 0);
    }

    return object? (t?(ulong)(hash[h].o):0) : (ulong)t;
}
