static char *_php_math_number_format_ex_len(double d, int dec, char *dec_point,
		size_t dec_point_len, char *thousand_sep, size_t thousand_sep_len,
		int *result_len)
{
	char *tmpbuf = NULL, *resbuf;
	char *s, *t;
	char *dp;
	int integral;
	int tmplen, reslen=0;
	int count=0;
	int is_negative=0;

	if (d < 0) {
		is_negative = 1;
		d = -d;
	}

	dec = MAX(0, dec);
	d = _php_math_round(d, dec, PHP_ROUND_HALF_UP);

	tmplen = spprintf(&tmpbuf, 0, "%.*F", dec, d);

	if (tmpbuf == NULL || !isdigit((int)tmpbuf[0])) {
		if (result_len) {
			*result_len = tmplen;
		}

		return tmpbuf;
	}


	if (dec) {
		dp = strpbrk(tmpbuf, ".,");
	} else {
		dp = NULL;
	}


	if (dp) {
		integral = dp - tmpbuf;
	} else {

		integral = tmplen;
	}


	if (thousand_sep) {
		integral += thousand_sep_len * ((integral-1) / 3);
	}

	reslen = integral;

	if (dec) {
		reslen += dec;

		if (dec_point) {
			reslen += dec_point_len;
		}
	}


	if (is_negative) {
		reslen++;
	}
	resbuf = (char *) emalloc(reslen+1);

	s = tmpbuf+tmplen-1;
	t = resbuf+reslen;
	*t-- = '\0';


	if (dec) {
		int declen = dp ? s - dp : 0;
		int topad = dec > declen ? dec - declen : 0;


		while (topad--) {
			*t-- = '0';
		}

		if (dp) {
			s -= declen + 1;
			t -= declen;


			memcpy(t + 1, dp + 1, declen);
		}


		if (dec_point) {
			t -= dec_point_len;
			memcpy(t + 1, dec_point, dec_point_len);
		}
	}


	while(s >= tmpbuf) {
		*t-- = *s--;
		if (thousand_sep && (++count%3)==0 && s>=tmpbuf) {
			t -= thousand_sep_len;
			memcpy(t + 1, thousand_sep, thousand_sep_len);
		}
	}


	if (is_negative) {
		*t-- = '-';
	}

	efree(tmpbuf);

	if (result_len) {
		*result_len = reslen;
	}

	return resbuf;
}
