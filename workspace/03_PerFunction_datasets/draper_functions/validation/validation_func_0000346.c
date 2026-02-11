fmt_class(struct spdet *up, const int fwidth)
{
	return  (fmt_t) strlen(strcpy(bigbuff, hex_disp(up? up->spu_class: Spuhdr.sph_class, 0)));
}
