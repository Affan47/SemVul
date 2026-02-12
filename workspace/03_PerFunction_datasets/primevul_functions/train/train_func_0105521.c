PERL_STATIC_INLINE char*
S_reg_skipcomment(RExC_state_t *pRExC_state, char* p)
{
    PERL_ARGS_ASSERT_REG_SKIPCOMMENT;

    assert(*p == '#');

    while (p < RExC_end) {
        if (*(++p) == '\n') {
            return p+1;
        }
    }


    RExC_seen |= REG_RUN_ON_COMMENT_SEEN;
    return p;
}
