enc_file_base64(PostAttachment *pa, FILE *fin, FILE *fout)
{
    unsigned char	buf[4];
    unsigned long	acc;
    int			n, pos = 0;

    while ((n = fread(buf, 1, 3, fin)) == 3) {
	acc = (buf[0] << 16) | (buf[1] << 8) | buf[2];
	buf[0] = base64_alpha[(acc >> 18) & 0x3fu];
	buf[1] = base64_alpha[(acc >> 12) & 0x3fu];
	buf[2] = base64_alpha[(acc >>  6) & 0x3fu];
	buf[3] = base64_alpha[(acc      ) & 0x3fu];
	fwrite(buf, 1, 4, fout);
	pos += 4;
	if (pos >= 76) {
	    fwrite("\r\n", 1, 2, fout);
	    pos = 0;
	}
    }

    switch (n) {
    case 1:
	acc = buf[0] << 16;
	buf[0] = base64_alpha[(acc >> 18) & 0x3ful];
	buf[1] = base64_alpha[(acc >> 12) & 0x3ful];
	buf[2] = '=';
	buf[3] = '=';
	fwrite(buf, 1, 4, fout);
	break;
    case 2:
	acc = (buf[0] << 16) | (buf[1] << 8);
	buf[0] = base64_alpha[(acc >> 18) & 0x3fu];
	buf[1] = base64_alpha[(acc >> 12) & 0x3fu];
	buf[2] = base64_alpha[(acc >>  6) & 0x3fu];
	buf[3] = '=';
	fwrite(buf, 1, 4, fout);
	break;
    }

    if (pos != 0)
	fwrite("\r\n", 1, 2, fout);
    fwrite("\r\n", 1, 2, fout);

    return True;
}
