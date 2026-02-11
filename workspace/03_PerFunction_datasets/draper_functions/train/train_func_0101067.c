decode_qp(char *dest, char *src, long len, int *soft, int underscore)
{
    long	src_pos, dest_pos;
    int		hex_no;

    if (soft)
	*soft = False;

    src_pos = dest_pos = 0;
    while (len > 0) {
	if (src[src_pos] == '=') {
	    if (len >= 2 && (hex_no = get_hex(src + src_pos + 1)) >= 0) {
		dest[dest_pos++] = hex_no;
		src += 3;
		len -= 3;
		continue;
	    } else if (rest_is_whitespace(src + src_pos + 1, len - 1)) {
		if (soft)
		    *soft = True;
		break;
	    }
	} else if (src[src_pos] == '_') {
	    if (underscore) {
		dest[dest_pos++] = ' ';
		src++;
		len--;
		continue;
	    }
	} else if (IS_SPACE(src[src_pos]) &&
		   rest_is_whitespace(src + src_pos + 1, len - 1))
	    break;

	dest[dest_pos++] = src[src_pos++];
	len--;
    }

    return dest_pos;
}
