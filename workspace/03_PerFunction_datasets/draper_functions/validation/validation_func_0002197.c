output(struct s_zstate *zs, code_int ocode)
{
	int r_off;
	unsigned bits;
	char_type *bp;

	r_off = offset;
	bits = n_bits;
	bp = buf;
	if (ocode >= 0) {

		bp += (r_off >> 3);
		r_off &= 7;


		*bp = (*bp & rmask[r_off]) | ((ocode << r_off) & lmask[r_off]);
		bp++;
		bits -= (8 - r_off);
		ocode >>= 8 - r_off;

		if (bits >= 8) {
			*bp++ = ocode;
			ocode >>= 8;
			bits -= 8;
		}

		if (bits)
			*bp = ocode;
		offset += n_bits;
		if (offset == (n_bits << 3)) {
			bp = buf;
			bits = n_bits;
			bytes_out += bits;
			if (fwrite(bp, sizeof(char), bits, fp) != bits)
				return (-1);
			bp += bits;
			bits = 0;
			offset = 0;
		}


		if (free_ent > maxcode || (clear_flg > 0)) {


			if (offset > 0) {
				if (fwrite(buf, 1, n_bits, fp) != n_bits)
					return (-1);
				bytes_out += n_bits;
			}
			offset = 0;

			if (clear_flg) {
				maxcode = MAXCODE(n_bits = INIT_BITS);
				clear_flg = 0;
			} else {
				n_bits++;
				if (n_bits == maxbits)
					maxcode = maxmaxcode;
				else
					maxcode = MAXCODE(n_bits);
			}
		}
	} else {

		if (offset > 0) {
			offset = (offset + 7) / 8;
			if (fwrite(buf, 1, offset, fp) != offset)
				return (-1);
			bytes_out += offset;
		}
		offset = 0;
	}
	return (0);
}
