PyMember_Get(const char *addr, struct memberlist *mlist, const char *name)
{
    struct memberlist *l;

    if (strcmp(name, "__members__") == 0)
        return listmembers(mlist);
    for (l = mlist; l->name != NULL; l++) {
        if (strcmp(l->name, name) == 0) {
            PyMemberDef copy;
            copy.name = l->name;
            copy.type = l->type;
            copy.offset = l->offset;
            copy.flags = l->flags;
            copy.doc = NULL;
            return PyMember_GetOne(addr, &copy);
        }
    }
    PyErr_SetString(PyExc_AttributeError, name);
    return NULL;
}
