pf_part2(font_info *fi, char **bufp, size_t *lenp) {
    t1_font *tf = fi->fontfile;

    if (tf->length2 == 0)
	tf->length2 = pf_length2(tf);
    pf_getbinary(tf, tf->length1, tf->length2, bufp, lenp);
    if (*lenp >= 256)
	*lenp -= 256;
}
