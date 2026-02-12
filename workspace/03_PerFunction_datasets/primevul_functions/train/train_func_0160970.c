int32_t DecimalQuantity::getUpperDisplayMagnitude() const {


    U_ASSERT(!isApproximate);

    int32_t magnitude = scale + precision;
    int32_t result = (lReqPos > magnitude) ? lReqPos : (lOptPos < magnitude) ? lOptPos : magnitude;
    return result - 1;
}
