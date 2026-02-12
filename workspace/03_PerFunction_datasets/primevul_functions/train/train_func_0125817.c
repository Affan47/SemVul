get_last_end_pos(asdl_seq *s, int *end_lineno, int *end_col_offset)
{
    int tot = asdl_seq_LEN(s);


    if (!tot) {
        return;
    }
    stmt_ty last = asdl_seq_GET(s, tot - 1);
    *end_lineno = last->end_lineno;
    *end_col_offset = last->end_col_offset;
}
