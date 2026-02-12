snmpLookupNodeStr(mib_tree_entry *root, const char *str)
{
    oid *name;
    int namelen;
    mib_tree_entry *e;

    if (root)
        e = root;
    else
        e = mib_tree_head;

    if (! snmpCreateOidFromStr(str, &name, &namelen))
        return NULL;


    if (namelen <= 1) {
        xfree(name);
        return e;
    }

    int i, r = 1;
    while (r < namelen) {


        for (i = 0; i < e->children && e->leaves[i]->name[r] != name[r]; ++i) ;


        if (i >= e->children)
            break;
        assert(e->leaves[i]->name[r] == name[r]);


        e = e->leaves[i];
        ++r;
    }

    xfree(name);
    return e;
}
