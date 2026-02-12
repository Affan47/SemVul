ast_for_async_stmt(struct compiling *c, const node *n)
{

    REQ(n, async_stmt);
    REQ(CHILD(n, 0), NAME);
    assert(strcmp(STR(CHILD(n, 0)), "async") == 0);

    switch (TYPE(CHILD(n, 1))) {
        case funcdef:
            return ast_for_funcdef_impl(c, n, NULL,
                                        true );
        case with_stmt:
            return ast_for_with_stmt(c, n,
                                     true );

        case for_stmt:
            return ast_for_for_stmt(c, n,
                                    true );

        default:
            PyErr_Format(PyExc_SystemError,
                         "invalid async stament: %s",
                         STR(CHILD(n, 1)));
            return NULL;
    }
}
