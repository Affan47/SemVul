get_pkcs_padding( unsigned char *input, size_t input_len,
        size_t *data_len )
{
    size_t i, pad_idx;
    unsigned char padding_len, bad = 0;

    if( NULL == input || NULL == data_len )
        return POLARSSL_ERR_CIPHER_BAD_INPUT_DATA;

    padding_len = input[input_len - 1];
    *data_len = input_len - padding_len;


    bad |= padding_len > input_len;
    bad |= padding_len == 0;


    pad_idx = input_len - padding_len;
    for( i = 0; i < input_len; i++ )
        bad |= ( input[i] ^ padding_len ) * ( i >= pad_idx );

    return POLARSSL_ERR_CIPHER_INVALID_PADDING * (bad != 0);
}
