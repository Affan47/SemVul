static inline operand_t readOperand(struct cli_bc_func *func, unsigned char *p,
				    unsigned *off, unsigned len, char *ok)
{
    uint64_t v;
    if ((p[*off]&0xf0) == 0x40 || p[*off] == 0x50) {
	uint64_t *dest;
	uint16_t ty;
	p[*off] |= 0x20;

	func->constants = cli_realloc2(func->constants, (func->numConstants+1)*sizeof(*func->constants));
	if (!func->constants) {
	    *ok = 0;
	    return MAX_OP;
	}
	v = readNumber(p, off, len, ok);
	dest = &func->constants[func->numConstants];


	*dest= 0;
	ty = 8*readFixedNumber(p, off, len, ok, 1);
	if (!ty) {

	    return 0x80000000 | v;
	}
	if (ty <= 8)
	    *(uint8_t*)dest = v;
	else if (ty <= 16)
	    *(uint16_t*)dest = v;
	else if (ty <= 32)
	    *(uint32_t*)dest = v;
	else
	    *dest = v;
	return func->numValues + func->numConstants++;
    }
    v = readNumber(p, off, len, ok);
    if (!*ok)
	return MAX_OP;
    if (v >= func->numValues) {
	cli_errmsg("Operand index exceeds bounds: %u >= %u!\n", (unsigned)v, (unsigned)func->numValues);
	*ok = 0;
	return MAX_OP;
    }
    return v;
}
