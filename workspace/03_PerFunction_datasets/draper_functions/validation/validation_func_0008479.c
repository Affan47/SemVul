setAll() {
    for (uint32_t i=0; i<sizeof(bits)/sizeof(uint32_t); i++) {
        bits[i] = 0xffffffffu;
    }
}
