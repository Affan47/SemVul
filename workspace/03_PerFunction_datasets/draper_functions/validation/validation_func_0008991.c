numaArithOp(NUMA    *nad,
            NUMA    *na1,
            NUMA    *na2,
            l_int32  op)
{
l_int32    i, n;
l_float32  val1, val2;

    PROCNAME("numaArithOp");

    if (!na1 || !na2)
        return (NUMA *)ERROR_PTR("na1, na2 not both defined", procName, nad);
    n = numaGetCount(na1);
    if (n != numaGetCount(na2))
        return (NUMA *)ERROR_PTR("na1, na2 sizes differ", procName, nad);
    if (nad && nad != na1)
        return (NUMA *)ERROR_PTR("nad defined but not in-place", procName, nad);
    if (op != L_ARITH_ADD && op != L_ARITH_SUBTRACT &&
        op != L_ARITH_MULTIPLY && op != L_ARITH_DIVIDE)
        return (NUMA *)ERROR_PTR("invalid op", procName, nad);
    if (op == L_ARITH_DIVIDE) {
        for (i = 0; i < n; i++) {
            numaGetFValue(na2, i, &val2);
            if (val2 == 0.0)
                return (NUMA *)ERROR_PTR("na2 has 0 element", procName, nad);
        }
    }


    if (!nad)
        nad = numaCopy(na1);

    for (i = 0; i < n; i++) {
        numaGetFValue(nad, i, &val1);
        numaGetFValue(na2, i, &val2);
        switch (op) {
        case L_ARITH_ADD:
            numaSetValue(nad, i, val1 + val2);
            break;
        case L_ARITH_SUBTRACT:
            numaSetValue(nad, i, val1 - val2);
            break;
        case L_ARITH_MULTIPLY:
            numaSetValue(nad, i, val1 * val2);
            break;
        case L_ARITH_DIVIDE:
            numaSetValue(nad, i, val1 / val2);
            break;
        default:
            fprintf(stderr, " Unknown arith op: %d\n", op);
            return nad;
        }
    }

    return nad;
}
