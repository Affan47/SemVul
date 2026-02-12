STATIC regnode_offset
S_regbranch(pTHX_ RExC_state_t *pRExC_state, I32 *flagp, I32 first, U32 depth)
{
    regnode_offset ret;
    regnode_offset chain = 0;
    regnode_offset latest;
    I32 flags = 0, c = 0;
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REGBRANCH;

    DEBUG_PARSE("brnc");

    if (first)
	ret = 0;
    else {
	if (RExC_use_BRANCHJ)
	    ret = reganode(pRExC_state, BRANCHJ, 0);
	else {
	    ret = reg_node(pRExC_state, BRANCH);
            Set_Node_Length(REGNODE_p(ret), 1);
        }
    }

    *flagp = WORST;

    skip_to_be_ignored_text(pRExC_state, &RExC_parse,
                            FALSE  );
    while (RExC_parse < RExC_end && *RExC_parse != '|' && *RExC_parse != ')') {
	flags &= ~TRYAGAIN;
        latest = regpiece(pRExC_state, &flags, depth+1);
	if (latest == 0) {
	    if (flags & TRYAGAIN)
		continue;
            RETURN_FAIL_ON_RESTART(flags, flagp);
            FAIL2("panic: regpiece returned failure, flags=%#" UVxf, (UV) flags);
	}
	else if (ret == 0)
            ret = latest;
	*flagp |= flags&(HASWIDTH|POSTPONED);
	if (chain == 0)
	    *flagp |= flags&SPSTART;
	else {


	    MARK_NAUGHTY(1);
            if (! REGTAIL(pRExC_state, chain, latest)) {


                REQUIRE_BRANCHJ(flagp, 0);
            }
	}
	chain = latest;
	c++;
    }
    if (chain == 0) {
	chain = reg_node(pRExC_state, NOTHING);
	if (ret == 0)
	    ret = chain;
    }
    if (c == 1) {
	*flagp |= flags&SIMPLE;
    }

    return ret;
}
