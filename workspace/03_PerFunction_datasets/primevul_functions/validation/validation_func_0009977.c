single_byte_optimizable(VALUE str)
{
    rb_encoding *enc;


    if (ENC_CODERANGE(str) == ENC_CODERANGE_7BIT)
        return 1;

    enc = STR_ENC_GET(str);
    if (rb_enc_mbmaxlen(enc) == 1)
        return 1;


    return 0;
}
