ast_for_starred(struct compiling *c, const node *n)
{
    expr_ty tmp;
    REQ(n, star_expr);

    tmp = ast_for_expr(c, CHILD(n, 1));
    if (!tmp)
        return NULL;


    return Starred(tmp, Load, LINENO(n), n->n_col_offset,
                   n->n_end_lineno, n->n_end_col_offset, c->c_arena);
}
