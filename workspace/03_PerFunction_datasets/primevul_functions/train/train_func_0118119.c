static void fstring_shift_node_locations(node *n, int lineno, int col_offset)
{
    int i;
    n->n_col_offset = n->n_col_offset + col_offset;
    for (i = 0; i < NCH(n); ++i) {
        if (n->n_lineno && n->n_lineno < CHILD(n, i)->n_lineno) {

            col_offset = 0;
        }
        fstring_shift_node_locations(CHILD(n, i), lineno, col_offset);
    }
    n->n_lineno = n->n_lineno + lineno;
}
