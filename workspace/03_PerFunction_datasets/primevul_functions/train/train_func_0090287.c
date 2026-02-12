md_analyze_bracket(MD_CTX* ctx, int mark_index)
{


    MD_MARK* mark = &ctx->marks[mark_index];

    if(mark->flags & MD_MARK_POTENTIAL_OPENER) {
        md_mark_chain_append(ctx, &BRACKET_OPENERS, mark_index);
        return;
    }

    if(BRACKET_OPENERS.tail >= 0) {

        int opener_index = BRACKET_OPENERS.tail;
        MD_MARK* opener = &ctx->marks[opener_index];
        if(opener->prev >= 0)
            ctx->marks[opener->prev].next = -1;
        else
            BRACKET_OPENERS.head = -1;
        BRACKET_OPENERS.tail = opener->prev;


        opener->next = mark_index;
        mark->prev = opener_index;


        if(ctx->unresolved_link_tail >= 0)
            ctx->marks[ctx->unresolved_link_tail].prev = opener_index;
        else
            ctx->unresolved_link_head = opener_index;
        ctx->unresolved_link_tail = opener_index;
        opener->prev = -1;
    }
}
