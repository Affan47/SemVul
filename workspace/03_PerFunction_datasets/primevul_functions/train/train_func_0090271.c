md_analyze_marks(MD_CTX* ctx, const MD_LINE* lines, int n_lines,
                 int mark_beg, int mark_end, const CHAR* mark_chars)
{
    int i = mark_beg;
    MD_UNUSED(lines);
    MD_UNUSED(n_lines);

    while(i < mark_end) {
        MD_MARK* mark = &ctx->marks[i];


        if(mark->flags & MD_MARK_RESOLVED) {
            if(mark->flags & MD_MARK_OPENER) {
                MD_ASSERT(i < mark->next);
                i = mark->next + 1;
            } else {
                i++;
            }
            continue;
        }


        if(!ISANYOF_(mark->ch, mark_chars)) {
            i++;
            continue;
        }


        switch(mark->ch) {
            case '[':
            case '!':
            case ']':   md_analyze_bracket(ctx, i); break;
            case '&':   md_analyze_entity(ctx, i); break;
            case '|':   md_analyze_table_cell_boundary(ctx, i); break;
            case '_':
            case '*':   md_analyze_emph(ctx, i); break;
            case '~':   md_analyze_tilde(ctx, i); break;
            case '$':   md_analyze_dollar(ctx, i); break;
            case '.':
            case ':':   md_analyze_permissive_url_autolink(ctx, i); break;
            case '@':   md_analyze_permissive_email_autolink(ctx, i); break;
        }

        i++;
    }
}
