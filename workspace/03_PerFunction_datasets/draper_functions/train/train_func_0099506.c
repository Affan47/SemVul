writeDeltaTo(int32_t jumpTarget) {
    int32_t i=ucharsLength-jumpTarget;
    U_ASSERT(i>=0);
    if(i<=UCharsTrie::kMaxOneUnitDelta) {
        return write(i);
    }
    UChar intUnits[3];
    int32_t length;
    if(i<=UCharsTrie::kMaxTwoUnitDelta) {
        intUnits[0]=(UChar)(UCharsTrie::kMinTwoUnitDeltaLead+(i>>16));
        length=1;
    } else {
        intUnits[0]=(UChar)(UCharsTrie::kThreeUnitDeltaLead);
        intUnits[1]=(UChar)(i>>16);
        length=2;
    }
    intUnits[length++]=(UChar)i;
    return write(intUnits, length);
}
