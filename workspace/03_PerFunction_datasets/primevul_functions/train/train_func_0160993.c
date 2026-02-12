void DecimalQuantity::readDoubleConversionToBcd(
        const char* buffer, int32_t length, int32_t point) {


    if (length > 16) {
        ensureCapacity(length);
        for (int32_t i = 0; i < length; i++) {
            fBCD.bcdBytes.ptr[i] = buffer[length-i-1] - '0';
        }
    } else {
        uint64_t result = 0L;
        for (int32_t i = 0; i < length; i++) {
            result |= static_cast<uint64_t>(buffer[length-i-1] - '0') << (4 * i);
        }
        fBCD.bcdLong = result;
    }
    scale = point - length;
    precision = length;
}
