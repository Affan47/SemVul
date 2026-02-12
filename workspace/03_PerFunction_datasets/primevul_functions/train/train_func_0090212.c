md_analyze_dollar(MD_CTX* ctx, int mark_index)
{


    if(DOLLAR_OPENERS.head >= 0) {

        MD_MARK* open = &ctx->marks[DOLLAR_OPENERS.head];
        MD_MARK* close = &ctx->marks[mark_index];

        int opener_index = DOLLAR_OPENERS.head;
        md_rollback(ctx, opener_index, mark_index, MD_ROLLBACK_ALL);
        if (open->end - open->beg == close->end - close->beg) {

            md_resolve_range(ctx, &DOLLAR_OPENERS, opener_index, mark_index);
        } else {

            md_mark_chain_append(ctx, &DOLLAR_OPENERS, mark_index);
        }
    } else {

        md_mark_chain_append(ctx, &DOLLAR_OPENERS, mark_index);
    }
}
