terminal_clear_screen(EditLine *el)
{

	if (GoodStr(T_cl))

		terminal_tputs(el, Str(T_cl), Val(T_li));
	else if (GoodStr(T_ho) && GoodStr(T_cd)) {
		terminal_tputs(el, Str(T_ho), Val(T_li));

		terminal_tputs(el, Str(T_cd), Val(T_li));
	} else {
		terminal__putc(el, '\r');
		terminal__putc(el, '\n');
	}
}
