int32_t DecimalQuantity::getLowerDisplayMagnitude() const {


    U_ASSERT(!isApproximate);

    int32_t magnitude = scale;
    int32_t result = (rReqPos < magnitude) ? rReqPos : (rOptPos > magnitude) ? rOptPos : magnitude;
    return result;
}
