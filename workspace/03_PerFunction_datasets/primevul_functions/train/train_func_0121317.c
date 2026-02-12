compiler_complex_args(struct compiling *c, const node *n)
{
    int i, len = (NCH(n) + 1) / 2;
    expr_ty result;
    asdl_seq *args = asdl_seq_new(len, c->c_arena);
    if (!args)
        return NULL;


    REQ(n, fplist);
    for (i = 0; i < len; i++) {
        PyObject *arg_id;
        const node *fpdef_node = CHILD(n, 2*i);
        const node *child;
        expr_ty arg;
set_name:

        child = CHILD(fpdef_node, 0);
        if (TYPE(child) == NAME) {
            if (!forbidden_check(c, n, STR(child)))
                return NULL;
            arg_id = NEW_IDENTIFIER(child);
            if (!arg_id)
                return NULL;
            arg = Name(arg_id, Store, LINENO(child), child->n_col_offset,
                       c->c_arena);
        }
        else {
            assert(TYPE(fpdef_node) == fpdef);

            child = CHILD(fpdef_node, 1);
            assert(TYPE(child) == fplist);

            if (NCH(child) == 1) {
                fpdef_node = CHILD(child, 0);
                assert(TYPE(fpdef_node) == fpdef);
                goto set_name;
            }
            arg = compiler_complex_args(c, child);
        }
        asdl_seq_SET(args, i, arg);
    }

    result = Tuple(args, Store, LINENO(n), n->n_col_offset, c->c_arena);
    if (!set_context(c, result, Store, n))
        return NULL;
    return result;
}
