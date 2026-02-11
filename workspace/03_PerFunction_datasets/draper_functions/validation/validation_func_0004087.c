Bit_Operation(Object b1, Object b2, void (*fun)()) {
    struct S_Bitstring *a, *b;

    Check_Type(b1, T_Bitstring);
    Check_Type(b2, T_Bitstring);
    a = BITSTRING(b1);
    b = BITSTRING(b2);
    if (a->len != b->len)
        Primitive_Error("bitstrings must have identical length");
    fun(a, b);
    return Void;
}
