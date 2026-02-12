ast_for_arguments(struct compiling *c, const node *n)
{


    int i, j, k, l, n_args = 0, n_all_args = 0, n_defaults = 0, found_default = 0;
    asdl_seq *args, *defaults, *type_comments = NULL;
    identifier vararg = NULL, kwarg = NULL;
    node *ch;

    if (TYPE(n) == parameters) {
        if (NCH(n) == 2)
            return arguments(NULL, NULL, NULL, NULL, NULL, c->c_arena);
        n = CHILD(n, 1);
    }
    REQ(n, varargslist);


    for (i = 0; i < NCH(n); i++) {
        ch = CHILD(n, i);
        if (TYPE(ch) == fpdef)
            n_args++;
        if (TYPE(ch) == EQUAL)
            n_defaults++;
        if (TYPE(ch) == STAR || TYPE(ch) == DOUBLESTAR)
            n_all_args++;
    }
    n_all_args += n_args;
    args = (n_args ? asdl_seq_new(n_args, c->c_arena) : NULL);
    if (!args && n_args)
        return NULL;
    defaults = (n_defaults ? asdl_seq_new(n_defaults, c->c_arena) : NULL);
    if (!defaults && n_defaults)
        return NULL;


    i = 0;
    j = 0;
    k = 0;
    l = 0;
    while (i < NCH(n)) {
        ch = CHILD(n, i);
        switch (TYPE(ch)) {
            case fpdef: {
                int complex_args = 0, parenthesized = 0;
            handle_fpdef:


                if (i + 1 < NCH(n) && TYPE(CHILD(n, i + 1)) == EQUAL) {
                    expr_ty expression = ast_for_expr(c, CHILD(n, i + 2));
                    if (!expression)
                        return NULL;
                    assert(defaults != NULL);
                    asdl_seq_SET(defaults, j++, expression);
                    i += 2;
                    found_default = 1;
                }
                else if (found_default) {


                    if (parenthesized && !complex_args) {
                        ast_error(n, "parenthesized arg with default");
                        return NULL;
                    }
                    ast_error(n,
                             "non-default argument follows default argument");
                    return NULL;
                }
                if (NCH(ch) == 3) {
                    ch = CHILD(ch, 1);

                    if (NCH(ch) != 1) {

                        if (Py_Py3kWarningFlag && !ast_warn(c, ch,
                            "tuple parameter unpacking has been removed in 3.x"))
                            return NULL;
                        complex_args = 1;
                        asdl_seq_SET(args, k++, compiler_complex_args(c, ch));
                        if (!asdl_seq_GET(args, k-1))
                                return NULL;
                    } else {


                        parenthesized = 1;
                        ch = CHILD(ch, 0);
                        assert(TYPE(ch) == fpdef);
                        goto handle_fpdef;
                    }
                }
                if (TYPE(CHILD(ch, 0)) == NAME) {
                    PyObject *id;
                    expr_ty name;
                    if (!forbidden_check(c, n, STR(CHILD(ch, 0))))
                        return NULL;
                    id = NEW_IDENTIFIER(CHILD(ch, 0));
                    if (!id)
                        return NULL;
                    name = Name(id, Param, LINENO(ch), ch->n_col_offset,
                                c->c_arena);
                    if (!name)
                        return NULL;
                    asdl_seq_SET(args, k++, name);

                }
                i += 1;
                if (i < NCH(n) && TYPE(CHILD(n, i)) == COMMA)
                    i += 1;
                if (parenthesized && Py_Py3kWarningFlag &&
                    !ast_warn(c, ch, "parenthesized argument names "
                              "are invalid in 3.x"))
                    return NULL;

                break;
            }
            case STAR:
                if (!forbidden_check(c, CHILD(n, i+1), STR(CHILD(n, i+1))))
                    return NULL;
                vararg = NEW_IDENTIFIER(CHILD(n, i+1));
                if (!vararg)
                    return NULL;
                i += 2;
                if (i < NCH(n) && TYPE(CHILD(n, i)) == COMMA)
                    i += 1;
                break;
            case DOUBLESTAR:
                if (!forbidden_check(c, CHILD(n, i+1), STR(CHILD(n, i+1))))
                    return NULL;
                kwarg = NEW_IDENTIFIER(CHILD(n, i+1));
                if (!kwarg)
                    return NULL;
                i += 2;
                if (i < NCH(n) && TYPE(CHILD(n, i)) == COMMA)
                    i += 1;
                break;
            case TYPE_COMMENT:
                assert(l < k + !!vararg + !!kwarg);

                if (!type_comments) {

                    type_comments = asdl_seq_new(n_all_args, c->c_arena);
                    if (!type_comments)
                        return NULL;
                }

                while (l < k + !!vararg + !!kwarg - 1) {
                    asdl_seq_SET(type_comments, l++, NULL);
                }

                asdl_seq_SET(type_comments, l++, NEW_TYPE_COMMENT(ch));
                i += 1;
                break;
            default:
                PyErr_Format(PyExc_SystemError,
                             "unexpected node in varargslist: %d @ %d",
                             TYPE(ch), i);
                return NULL;
        }
    }

    if (type_comments) {
        while (l < n_all_args) {
            asdl_seq_SET(type_comments, l++, NULL);
        }
    }

    return arguments(args, vararg, kwarg, defaults, type_comments, c->c_arena);
}
