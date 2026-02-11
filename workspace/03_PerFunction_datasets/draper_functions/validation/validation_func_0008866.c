cf_tai64_op_serialize
   (value v, unsigned long* size32Ptr, unsigned long* size64Ptr)
{
    CAMLparam1(v);

    char buffer[8];
    unsigned long long x;
    int i;

    x = Cf_tai64_val(v)->s;
    for (i = 7; i >= 0; --i) {
        u_int8_t ch = x & 0xFFULL;
        x >>= 8;
        buffer[i] = (char) ch;
    }

    serialize_block_1(buffer, 8);
    *size32Ptr = 8;
    *size64Ptr = 8;

    CAMLreturn0;
}
