quoted_hex() const
{
    static const char hex_digits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    StringAccum sa;
    char *buf;
    if (out_of_memory() || !(buf = sa.extend(length() * 2 + 3)))
	return make_out_of_memory();
    *buf++ = '\\';
    *buf++ = '<';
    const uint8_t *e = reinterpret_cast<const uint8_t*>(end());
    for (const uint8_t *x = reinterpret_cast<const uint8_t*>(begin()); x < e; x++) {
	*buf++ = hex_digits[(*x >> 4) & 0xF];
	*buf++ = hex_digits[*x & 0xF];
    }
    *buf++ = '>';
    return sa.take_string();
}
