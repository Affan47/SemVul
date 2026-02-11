roundAndPackFloat32(int zSign, Bit16s zExp, Bit32u zSig, float_status_t &status)
{
    Bit32s roundIncrement, roundBits, roundMask;

    int roundingMode = get_float_rounding_mode(status);
    int roundNearestEven = (roundingMode == float_round_nearest_even);
    roundIncrement = 0x40;
    roundMask = 0x7F;

    if (! roundNearestEven) {
        if (roundingMode == float_round_to_zero) roundIncrement = 0;
        else {
            roundIncrement = roundMask;
            if (zSign) {
                if (roundingMode == float_round_up) roundIncrement = 0;
            }
            else {
                if (roundingMode == float_round_down) roundIncrement = 0;
            }
        }
    }
    roundBits = zSig & roundMask;
    if (0xFD <= (Bit16u) zExp) {
        if ((0xFD < zExp)
             || ((zExp == 0xFD)
                  && ((Bit32s) (zSig + roundIncrement) < 0)))
        {
            float_raise(status, float_flag_overflow | float_flag_inexact);
            if (roundIncrement != 0) set_float_rounding_up(status);
            return packFloat32(zSign, 0xFF, 0) - (roundIncrement == 0);
        }
        if (zExp < 0) {
            int isTiny = (zExp < -1) || (zSig + roundIncrement < 0x80000000);
            zSig = shift32RightJamming(zSig, -zExp);
            zExp = 0;
            roundBits = zSig & roundMask;
            if (isTiny && (roundBits || !float_exception_masked(status, float_flag_underflow))) {
                float_raise(status, float_flag_underflow);
                if(get_flush_underflow_to_zero(status)) {
                    float_raise(status, float_flag_inexact);
                    return packFloat32(zSign, 0, 0);
                }
            }
        }
    }
    if (roundBits) float_raise(status, float_flag_inexact);
    Bit32u zSigRound = ((zSig + roundIncrement) & ~roundMask) >> 7;
    zSigRound &= ~(((roundBits ^ 0x40) == 0) & roundNearestEven);
    if ((zSigRound << 7) > zSig) set_float_rounding_up(status);
    if (zSigRound == 0) zExp = 0;
    return packFloat32(zSign, zExp, zSigRound);
}
