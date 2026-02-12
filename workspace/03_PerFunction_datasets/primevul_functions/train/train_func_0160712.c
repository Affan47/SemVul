void DecimalQuantity::setIntegerLength(int32_t minInt, int32_t maxInt) {

    U_ASSERT(minInt >= 0);
    U_ASSERT(maxInt >= minInt);


    if (minInt < lReqPos) {
        minInt = lReqPos;
    }


    lOptPos = maxInt;
    lReqPos = minInt;
}
