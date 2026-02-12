void DecimalQuantity::setFractionLength(int32_t minFrac, int32_t maxFrac) {

    U_ASSERT(minFrac >= 0);
    U_ASSERT(maxFrac >= minFrac);


    rReqPos = -minFrac;
    rOptPos = -maxFrac;
}
