orderfunc (void *data, Gawdata_t *dp) {
    txtnode_t *pnode, *cnode;
    int i;

    pnode = data;
    dp->cj = 0;
    for (i = 0, cnode = &pnode->u.f.t.list[0]; i < pnode->u.f.t.n; i++, cnode++)
        switch (cnode->mode) {
        case TXT_SEEN:
            dp->carray[dp->cj++].w = Gwidgets[cnode->u.s.wi].w;
            break;
        case TXT_ABSTRACT:
            dp->carray[dp->cj++].w = Gwidgets[cnode->u.a.wi].w;
            break;
        case TXT_FULL:
            if (cnode->ttype == T_TABLE) {
                dp->carray[dp->cj++].w = Gwidgets[cnode->u.f.t.fwi].w;
                dp->carray[dp->cj++].w = Gwidgets[cnode->u.f.t.mwi].w;
                dp->carray[dp->cj++].w = Gwidgets[cnode->u.f.t.lwi].w;
            } else
                dp->carray[dp->cj++].w = Gwidgets[cnode->u.f.s.wi].w;
            break;
        }
}
