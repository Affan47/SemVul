ast_for_async_funcdef(struct compiling *c, const node *n, asdl_seq *decorator_seq)
{

    REQ(n, async_funcdef);
    REQ(CHILD(n, 0), NAME);
    assert(strcmp(STR(CHILD(n, 0)), "async") == 0);
    REQ(CHILD(n, 1), funcdef);

    return ast_for_funcdef_impl(c, n, decorator_seq,
                                true );
}
