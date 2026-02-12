clear_selection(void) {
	highlight_pointer(-1);
	if (sel_start != -1) {
		highlight(sel_start, sel_end);
		sel_start = -1;
	}
}
