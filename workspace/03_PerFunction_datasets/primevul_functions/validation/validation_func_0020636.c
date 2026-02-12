need_conversion(char_u *fenc)
{
    int		same_encoding;
    int		enc_flags;
    int		fenc_flags;

    if (*fenc == NUL || STRCMP(p_enc, fenc) == 0)
    {
	same_encoding = TRUE;
	fenc_flags = 0;
    }
    else
    {


	enc_flags = get_fio_flags(p_enc);
	fenc_flags = get_fio_flags(fenc);
	same_encoding = (enc_flags != 0 && fenc_flags == enc_flags);
    }
    if (same_encoding)
    {


	return enc_unicode != 0;
    }


    return !(enc_utf8 && fenc_flags == FIO_UTF8);
}
