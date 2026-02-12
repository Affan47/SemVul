void vc_uniscr_copy_line(struct vc_data *vc, void *dest, int viewed,
			 unsigned int row, unsigned int col, unsigned int nr)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);
	int offset = row * vc->vc_size_row + col * 2;
	unsigned long pos;

	BUG_ON(!uniscr);

	pos = (unsigned long)screenpos(vc, offset, viewed);
	if (pos >= vc->vc_origin && pos < vc->vc_scr_end) {


		row = (pos - vc->vc_origin) / vc->vc_size_row;
		col = ((pos - vc->vc_origin) % vc->vc_size_row) / 2;
		memcpy(dest, &uniscr->lines[row][col], nr * sizeof(char32_t));
	} else {


		u16 *p = (u16 *)pos;
		int mask = vc->vc_hi_font_mask | 0xff;
		char32_t *uni_buf = dest;
		while (nr--) {
			u16 glyph = scr_readw(p++) & mask;
			*uni_buf++ = inverse_translate(vc, glyph, true);
		}
	}
}
