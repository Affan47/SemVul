PyInt_ClearFreeList(void)
{
    PyIntObject *p;
    PyIntBlock *list, *next;
    int i;
    int u;
    int freelist_size = 0;

    list = block_list;
    block_list = NULL;
    free_list = NULL;
    while (list != NULL) {
        u = 0;
        for (i = 0, p = &list->objects[0];
             i < N_INTOBJECTS;
             i++, p++) {
            if (PyInt_CheckExact(p) && p->ob_refcnt != 0)
                u++;
        }
        next = list->next;
        if (u) {
            list->next = block_list;
            block_list = list;
            for (i = 0, p = &list->objects[0];
                 i < N_INTOBJECTS;
                 i++, p++) {
                if (!PyInt_CheckExact(p) ||
                    p->ob_refcnt == 0) {
                    Py_TYPE(p) = (struct _typeobject *)
                        free_list;
                    free_list = p;
                }
#if NSMALLNEGINTS + NSMALLPOSINTS > 0
                else if (-NSMALLNEGINTS <= p->ob_ival &&
                         p->ob_ival < NSMALLPOSINTS &&
                         small_ints[p->ob_ival +
                                    NSMALLNEGINTS] == NULL) {
                    Py_INCREF(p);
                    small_ints[p->ob_ival +
                               NSMALLNEGINTS] = p;
                }
#endif
            }
        }
        else {
            PyMem_FREE(list);
        }
        freelist_size += u;
        list = next;
    }

    return freelist_size;
}
