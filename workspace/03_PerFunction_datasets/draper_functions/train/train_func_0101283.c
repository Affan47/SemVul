mono_decimalFloorAndTrunc(decimal_repr* pA, gint32 floorFlag)
{
    guint64 alo, ahi;
    guint32 factor, rest;
    int scale, sign, idx;
    int hasRest = 0;

    MONO_ARCH_SAVE_REGS;

    scale = pA->signscale.scale;
    if (scale == 0) return;

    DECTO128(pA, alo, ahi);
    sign = pA->signscale.sign;

    while (scale > 0) {
        idx = (scale > DECIMAL_MAX_INTFACTORS) ? DECIMAL_MAX_INTFACTORS : scale;
        factor = constantsDecadeInt32Factors[idx];
        scale -= idx;
        div128by32(&alo, &ahi, factor, &rest);
        hasRest = hasRest || (rest != 0);
    }

    if (floorFlag && hasRest && sign) {
        roundUp128(&alo, &ahi);
    }

    pack128toDecimal(pA, alo, ahi, 0, sign);
}
