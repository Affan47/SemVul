ecc_checksector(
    const uint8_t *address,
    const uint8_t *data,
    const uint8_t *ecc
) {
    return
        ecc_checkpq(address, data, 86, 24,  2, 86, ecc) &&
        ecc_checkpq(address, data, 52, 43, 86, 88, ecc + 0xAC);
}
