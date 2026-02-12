ref_stack_push(ref_stack_t *pstack, uint count)
{


    uint needed = count;
    uint added;

    for (; (added = pstack->top - pstack->p) < needed; needed -= added) {
        int code;

        pstack->p = pstack->top;
        code = ref_stack_push_block(pstack,
                                    (pstack->top - pstack->bot + 1) / 3,
                                    added);
        if (code < 0) {

            ref_stack_pop(pstack, count - needed + added);
            pstack->requested = count;
            return code;
        }
    }
    pstack->p += needed;
    return 0;
}
