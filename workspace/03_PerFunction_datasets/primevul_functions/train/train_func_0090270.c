md_is_opening_code_fence(MD_CTX* ctx, OFF beg, OFF* p_end)
{
    OFF off = beg;

    while(off < ctx->size && CH(off) == CH(beg))
        off++;


    if(off - beg < 3)
        return FALSE;

    ctx->code_fence_length = off - beg;


    while(off < ctx->size  &&  CH(off) == _T(' '))
        off++;


    while(off < ctx->size  &&  !ISNEWLINE(off)) {

        if(CH(beg) == _T('`')  &&  CH(off) == _T('`'))
            return FALSE;
        off++;
    }

    *p_end = off;
    return TRUE;
}
