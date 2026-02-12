buf_write_bytes(struct bw_info *ip)
{
    int		wlen;
    char_u	*buf = ip->bw_buf;
    int		len = ip->bw_len;
#ifdef HAS_BW_FLAGS
    int		flags = ip->bw_flags;
#endif

#ifdef FEAT_MBYTE


    if (!(flags & FIO_NOCONVERT))
    {
	char_u		*p;
	unsigned	c;
	int		n;

	if (flags & FIO_UTF8)
	{


	    p = ip->bw_conv_buf;
	    for (wlen = 0; wlen < len; ++wlen)
		p += utf_char2bytes(buf[wlen], p);
	    buf = ip->bw_conv_buf;
	    len = (int)(p - ip->bw_conv_buf);
	}
	else if (flags & (FIO_UCS4 | FIO_UTF16 | FIO_UCS2 | FIO_LATIN1))
	{


	    if (flags & FIO_LATIN1)
		p = buf;
	    else
		p = ip->bw_conv_buf;
	    for (wlen = 0; wlen < len; wlen += n)
	    {
		if (wlen == 0 && ip->bw_restlen != 0)
		{
		    int		l;


		    l = CONV_RESTLEN - ip->bw_restlen;
		    if (l > len)
			l = len;
		    mch_memmove(ip->bw_rest + ip->bw_restlen, buf, (size_t)l);
		    n = utf_ptr2len_len(ip->bw_rest, ip->bw_restlen + l);
		    if (n > ip->bw_restlen + len)
		    {


			if (ip->bw_restlen + len > CONV_RESTLEN)
			    return FAIL;
			ip->bw_restlen += len;
			break;
		    }
		    if (n > 1)
			c = utf_ptr2char(ip->bw_rest);
		    else
			c = ip->bw_rest[0];
		    if (n >= ip->bw_restlen)
		    {
			n -= ip->bw_restlen;
			ip->bw_restlen = 0;
		    }
		    else
		    {
			ip->bw_restlen -= n;
			mch_memmove(ip->bw_rest, ip->bw_rest + n,
						      (size_t)ip->bw_restlen);
			n = 0;
		    }
		}
		else
		{
		    n = utf_ptr2len_len(buf + wlen, len - wlen);
		    if (n > len - wlen)
		    {


			if (len - wlen > CONV_RESTLEN)
			    return FAIL;
			ip->bw_restlen = len - wlen;
			mch_memmove(ip->bw_rest, buf + wlen,
						      (size_t)ip->bw_restlen);
			break;
		    }
		    if (n > 1)
			c = utf_ptr2char(buf + wlen);
		    else
			c = buf[wlen];
		}

		if (ucs2bytes(c, &p, flags) && !ip->bw_conv_error)
		{
		    ip->bw_conv_error = TRUE;
		    ip->bw_conv_error_lnum = ip->bw_start_lnum;
		}
		if (c == NL)
		    ++ip->bw_start_lnum;
	    }
	    if (flags & FIO_LATIN1)
		len = (int)(p - buf);
	    else
	    {
		buf = ip->bw_conv_buf;
		len = (int)(p - ip->bw_conv_buf);
	    }
	}

# ifdef WIN3264
	else if (flags & FIO_CODEPAGE)
	{


	    char_u	*from;
	    size_t	fromlen;
	    char_u	*to;
	    int		u8c;
	    BOOL	bad = FALSE;
	    int		needed;

	    if (ip->bw_restlen > 0)
	    {


		fromlen = len + ip->bw_restlen;
		from = ip->bw_conv_buf + ip->bw_conv_buflen - fromlen;
		mch_memmove(from, ip->bw_rest, (size_t)ip->bw_restlen);
		mch_memmove(from + ip->bw_restlen, buf, (size_t)len);
	    }
	    else
	    {
		from = buf;
		fromlen = len;
	    }

	    to = ip->bw_conv_buf;
	    if (enc_utf8)
	    {


		while (fromlen > 0)
		{
		    n = (int)utf_ptr2len_len(from, (int)fromlen);
		    if (n > (int)fromlen)
			break;
		    u8c = utf_ptr2char(from);
		    *to++ = (u8c & 0xff);
		    *to++ = (u8c >> 8);
		    fromlen -= n;
		    from += n;
		}


		if (fromlen > CONV_RESTLEN)
		{

		    ip->bw_conv_error = TRUE;
		    return FAIL;
		}
		mch_memmove(ip->bw_rest, from, fromlen);
		ip->bw_restlen = (int)fromlen;
	    }
	    else
	    {


		ip->bw_restlen = 0;
		needed = MultiByteToWideChar(enc_codepage,
			     MB_ERR_INVALID_CHARS, (LPCSTR)from, (int)fromlen,
								     NULL, 0);
		if (needed == 0)
		{

		    needed = MultiByteToWideChar(enc_codepage,
			 MB_ERR_INVALID_CHARS, (LPCSTR)from, (int)fromlen - 1,
								     NULL, 0);
		    if (needed == 0)
		    {

			ip->bw_conv_error = TRUE;
			return FAIL;
		    }

		    ip->bw_rest[0] = from[fromlen - 1];
		    ip->bw_restlen = 1;
		}
		needed = MultiByteToWideChar(enc_codepage, MB_ERR_INVALID_CHARS,
				(LPCSTR)from, (int)(fromlen - ip->bw_restlen),
							  (LPWSTR)to, needed);
		if (needed == 0)
		{

		    ip->bw_conv_error = TRUE;
		    return FAIL;
		}
		to += needed * 2;
	    }

	    fromlen = to - ip->bw_conv_buf;
	    buf = to;
#  ifdef CP_UTF8
	    if (FIO_GET_CP(flags) == CP_UTF8)
	    {


		for (from = ip->bw_conv_buf; fromlen > 1; fromlen -= 2)
		{
		    u8c = *from++;
		    u8c += (*from++ << 8);
		    to += utf_char2bytes(u8c, to);
		    if (to + 6 >= ip->bw_conv_buf + ip->bw_conv_buflen)
		    {
			ip->bw_conv_error = TRUE;
			return FAIL;
		    }
		}
		len = (int)(to - buf);
	    }
	    else
#endif
	    {


		len = WideCharToMultiByte(FIO_GET_CP(flags), 0,
			(LPCWSTR)ip->bw_conv_buf, (int)fromlen / sizeof(WCHAR),
			(LPSTR)to, (int)(ip->bw_conv_buflen - fromlen), 0,
									&bad);
		if (bad)
		{
		    ip->bw_conv_error = TRUE;
		    return FAIL;
		}
	    }
	}
# endif

# ifdef MACOS_CONVERT
	else if (flags & FIO_MACROMAN)
	{


	    char_u	*from;
	    size_t	fromlen;

	    if (ip->bw_restlen > 0)
	    {


		fromlen = len + ip->bw_restlen;
		from = ip->bw_conv_buf + ip->bw_conv_buflen - fromlen;
		mch_memmove(from, ip->bw_rest, (size_t)ip->bw_restlen);
		mch_memmove(from + ip->bw_restlen, buf, (size_t)len);
	    }
	    else
	    {
		from = buf;
		fromlen = len;
	    }

	    if (enc2macroman(from, fromlen,
			ip->bw_conv_buf, &len, ip->bw_conv_buflen,
			ip->bw_rest, &ip->bw_restlen) == FAIL)
	    {
		ip->bw_conv_error = TRUE;
		return FAIL;
	    }
	    buf = ip->bw_conv_buf;
	}
# endif

# ifdef USE_ICONV
	if (ip->bw_iconv_fd != (iconv_t)-1)
	{
	    const char	*from;
	    size_t	fromlen;
	    char	*to;
	    size_t	tolen;


	    if (ip->bw_restlen > 0)
	    {
		char *fp;


		fromlen = len + ip->bw_restlen;
		fp = (char *)ip->bw_conv_buf + ip->bw_conv_buflen - fromlen;
		mch_memmove(fp, ip->bw_rest, (size_t)ip->bw_restlen);
		mch_memmove(fp + ip->bw_restlen, buf, (size_t)len);
		from = fp;
		tolen = ip->bw_conv_buflen - fromlen;
	    }
	    else
	    {
		from = (const char *)buf;
		fromlen = len;
		tolen = ip->bw_conv_buflen;
	    }
	    to = (char *)ip->bw_conv_buf;

	    if (ip->bw_first)
	    {
		size_t	save_len = tolen;


		(void)iconv(ip->bw_iconv_fd, NULL, NULL, &to, &tolen);


		if (to == NULL)
		{
		    to = (char *)ip->bw_conv_buf;
		    tolen = save_len;
		}
		ip->bw_first = FALSE;
	    }


	    if ((iconv(ip->bw_iconv_fd, (void *)&from, &fromlen, &to, &tolen)
			== (size_t)-1 && ICONV_ERRNO != ICONV_EINVAL)
						    || fromlen > CONV_RESTLEN)
	    {
		ip->bw_conv_error = TRUE;
		return FAIL;
	    }


	    if (fromlen > 0)
		mch_memmove(ip->bw_rest, (void *)from, fromlen);
	    ip->bw_restlen = (int)fromlen;

	    buf = ip->bw_conv_buf;
	    len = (int)((char_u *)to - ip->bw_conv_buf);
	}
# endif
    }
#endif

    if (ip->bw_fd < 0)

	return OK;

#ifdef FEAT_CRYPT
    if (flags & FIO_ENCRYPTED)
    {


	if (crypt_works_inplace(ip->bw_buffer->b_cryptstate))
	{
	    crypt_encode_inplace(ip->bw_buffer->b_cryptstate, buf, len);
	}
	else
	{
	    char_u *outbuf;

	    len = crypt_encode_alloc(curbuf->b_cryptstate, buf, len, &outbuf);
	    if (len == 0)
		return OK;
	    wlen = write_eintr(ip->bw_fd, outbuf, len);
	    vim_free(outbuf);
	    return (wlen < len) ? FAIL : OK;
	}
    }
#endif

    wlen = write_eintr(ip->bw_fd, buf, len);
    return (wlen < len) ? FAIL : OK;
}
