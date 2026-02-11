operator+(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_add(r.fValue, fValue, num.fValue);
    return r;
}
