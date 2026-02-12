md_analyze_inlines(MD_CTX* ctx, const MD_LINE* lines, int n_lines, int table_mode)
{
    int ret;


    ctx->n_marks = 0;


    MD_CHECK(md_collect_marks(ctx, lines, n_lines, table_mode));


    md_analyze_marks(ctx, lines, n_lines, 0, ctx->n_marks, _T("&"));


    md_analyze_marks(ctx, lines, n_lines, 0, ctx->n_marks, _T("[]!"));
    MD_CHECK(md_resolve_links(ctx, lines, n_lines));
    BRACKET_OPENERS.head = -1;
    BRACKET_OPENERS.tail = -1;
    ctx->unresolved_link_head = -1;
    ctx->unresolved_link_tail = -1;

    if(table_mode) {


        MD_ASSERT(n_lines == 1);
        TABLECELLBOUNDARIES.head = -1;
        TABLECELLBOUNDARIES.tail = -1;
        ctx->n_table_cell_boundaries = 0;
        md_analyze_marks(ctx, lines, n_lines, 0, ctx->n_marks, _T("|"));
        return ret;
    }


    md_analyze_link_contents(ctx, lines, n_lines, 0, ctx->n_marks);

abort:
    return ret;
}
