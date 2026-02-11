rb_str_concat(VALUE str1, VALUE str2)
{
    unsigned int code;
    rb_encoding *enc = STR_ENC_GET(str1);

    if (FIXNUM_P(str2) || TYPE(str2) == T_BIGNUM) {
	if (rb_num_to_uint(str2, &code) == 0) {
	}
	else if (FIXNUM_P(str2)) {
	    rb_raise(rb_eRangeError, "%ld out of char range", FIX2LONG(str2));
	}
	else {
	    rb_raise(rb_eRangeError, "bignum out of char range");
	}
    }
    else {
	return rb_str_append(str1, str2);
    }

    if (enc == rb_usascii_encoding()) {

	char buf[1];
	buf[0] = (char)code;
	if (code > 0xFF) {
	    rb_raise(rb_eRangeError, "%u out of char range", code);
	}
	rb_str_cat(str1, buf, 1);
	if (code > 127) {
	    rb_enc_associate(str1, rb_ascii8bit_encoding());
	    ENC_CODERANGE_SET(str1, ENC_CODERANGE_VALID);
	}
    }
    else {
	long pos = RSTRING_LEN(str1);
	int cr = ENC_CODERANGE(str1);
	int len;
	char *buf;

	switch (len = rb_enc_codelen(code, enc)) {
	  case ONIGERR_INVALID_CODE_POINT_VALUE:
	    rb_raise(rb_eRangeError, "invalid codepoint 0x%X in %s", code, rb_enc_name(enc));
	    break;
	  case ONIGERR_TOO_BIG_WIDE_CHAR_VALUE:
	  case 0:
	    rb_raise(rb_eRangeError, "%u out of char range", code);
	    break;
	}
	buf = ALLOCA_N(char, len + 1);
	rb_enc_mbcput(code, buf, enc);
	if (rb_enc_precise_mbclen(buf, buf + len + 1, enc) != len) {
	    rb_raise(rb_eRangeError, "invalid codepoint 0x%X in %s", code, rb_enc_name(enc));
	}
	rb_str_resize(str1, pos+len);
	strncpy(RSTRING_PTR(str1) + pos, buf, len);
	if (cr == ENC_CODERANGE_7BIT && code > 127)
	    cr = ENC_CODERANGE_VALID;
	ENC_CODERANGE_SET(str1, cr);
    }
    return str1;
}
