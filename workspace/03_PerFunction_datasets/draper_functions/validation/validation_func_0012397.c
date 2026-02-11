unapply(ht_text_editor *te, bool *goto_only)
{
	if (*goto_only && (bpos.line != te->top_line + te->cursory || te->physical_cursorx()!=bpos.pofs)) {
		te->goto_line(apos.line);
		te->cursor_pput(apos.pofs);
		te->goto_line(bpos.line);
		te->cursor_pput(bpos.pofs);
		return;
	}
	*goto_only = false;
	delete_text_block(te, bpos, apos, cpos, sel_start, sel_end, false, NULL, NULL);
}
