PyNode_AddChild(register node *n1, int type, char *str, int lineno, int col_offset)
{
    const int nch = n1->n_nchildren;
    int current_capacity;
    int required_capacity;
    node *n;

    if (nch == INT_MAX || nch < 0)
        return E_OVERFLOW;

    current_capacity = XXXROUNDUP(nch);
    required_capacity = XXXROUNDUP(nch + 1);
    if (current_capacity < 0 || required_capacity < 0)
        return E_OVERFLOW;
    if (current_capacity < required_capacity) {
        if (required_capacity > PY_SIZE_MAX / sizeof(node)) {
            return E_NOMEM;
        }
        n = n1->n_child;
        n = (node *) PyObject_REALLOC(n,
                                      required_capacity * sizeof(node));
        if (n == NULL)
            return E_NOMEM;
        n1->n_child = n;
    }

    n = &n1->n_child[n1->n_nchildren++];
    n->n_type = type;
    n->n_str = str;
    n->n_lineno = lineno;
    n->n_col_offset = col_offset;
    n->n_nchildren = 0;
    n->n_child = NULL;
    return 0;
}
