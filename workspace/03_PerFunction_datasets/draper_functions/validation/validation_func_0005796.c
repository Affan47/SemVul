_fetch_operand(HDMV_VM *p, int setstream, int setbuttonpage, int imm, uint32_t value)
{
    if (imm) {
        return value;
    }

    if (setstream) {
        return _read_setstream_regs(p, value);

    } else if (setbuttonpage) {
        return _read_setbuttonpage_reg(p, value);

    } else {
        return _read_reg(p, value);
    }
}
