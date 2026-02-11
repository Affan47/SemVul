VpSubAbs(Real *a, Real *b, Real *c)
{
    size_t word_shift;
    size_t ap;
    size_t bp;
    size_t cp;
    size_t a_pos;
    size_t b_pos, b_pos_with_word_shift;
    size_t c_pos;
    BDIGIT av, bv, borrow, mrv;

#ifdef BIGDECIMAL_DEBUG
    if(gfDebug) {
        VPrint(stdout, "VpSubAbs called: a = %\n", a);
        VPrint(stdout, "     b = %\n", b);
    }
#endif

    word_shift = VpSetPTR(a, b, c, &ap, &bp, &cp, &av, &bv);
    a_pos = ap;
    b_pos = bp;
    c_pos = cp;
    if(word_shift==(size_t)-1L) return 0;
    if(b_pos == (size_t)-1L) goto Assign_a;

    if(av >= bv) {
        mrv = av - bv;
        borrow = 0;
    } else {
        mrv    = 0;
        borrow = 1;
    }


    if(b_pos + word_shift > a_pos) {
        while(b_pos + word_shift > a_pos) {
            --c_pos;
            if(b_pos > 0) {
                c->frac[c_pos] = BASE - b->frac[--b_pos] - borrow;
            } else {
                --word_shift;
                c->frac[c_pos] = BASE - borrow;
            }
            borrow = 1;
        }
    }


    b_pos_with_word_shift = b_pos + word_shift;
    while(a_pos > b_pos_with_word_shift) {
        c->frac[--c_pos] = a->frac[--a_pos];
    }


    while(b_pos > 0) {
        --c_pos;
        if(a->frac[--a_pos] < b->frac[--b_pos] + borrow) {
            c->frac[c_pos] = BASE + a->frac[a_pos] - b->frac[b_pos] - borrow;
            borrow = 1;
        } else {
            c->frac[c_pos] = a->frac[a_pos] - b->frac[b_pos] - borrow;
            borrow = 0;
        }
    }


    while(a_pos > 0) {
        --c_pos;
        if(a->frac[--a_pos] < borrow) {
            c->frac[c_pos] = BASE + a->frac[a_pos] - borrow;
            borrow = 1;
        } else {
            c->frac[c_pos] = a->frac[a_pos] - borrow;
            borrow = 0;
        }
    }
    if(c_pos) c->frac[c_pos - 1] -= borrow;
    goto Exit;

Assign_a:
    VpAsgn(c, a, 1);
    mrv = 0;

Exit:
#ifdef BIGDECIMAL_DEBUG
    if(gfDebug) {
        VPrint(stdout, "VpSubAbs exit: c=% \n", c);
    }
#endif
    return mrv;
}
