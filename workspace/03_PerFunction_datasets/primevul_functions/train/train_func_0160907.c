void DecimalQuantity::ensureCapacity(int32_t capacity) {
    if (capacity == 0) { return; }
    int32_t oldCapacity = usingBytes ? fBCD.bcdBytes.len : 0;
    if (!usingBytes) {


        fBCD.bcdBytes.ptr = static_cast<int8_t*>(uprv_malloc(capacity * sizeof(int8_t)));
        fBCD.bcdBytes.len = capacity;

        uprv_memset(fBCD.bcdBytes.ptr, 0, capacity * sizeof(int8_t));
    } else if (oldCapacity < capacity) {
        auto bcd1 = static_cast<int8_t*>(uprv_malloc(capacity * 2 * sizeof(int8_t)));
        uprv_memcpy(bcd1, fBCD.bcdBytes.ptr, oldCapacity * sizeof(int8_t));

        uprv_memset(bcd1 + oldCapacity, 0, (capacity - oldCapacity) * sizeof(int8_t));
        uprv_free(fBCD.bcdBytes.ptr);
        fBCD.bcdBytes.ptr = bcd1;
        fBCD.bcdBytes.len = capacity * 2;
    }
    usingBytes = true;
}
