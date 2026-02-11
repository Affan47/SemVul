gr_stringwidth(const char *s, double *w, double *a, double *d)
{
	*w = *a = *d = 0.0;
	if (strlen(s) == 0)
		return;
	bool            used_supers = false;
	bool            used_subs = false;
	bool            inmath = false;
	bool            oldWritePS = _grWritePS;
	double          oldfontsize_pt = gr_currentfontsize_pt();
	_grWritePS = false;
	while (*s != '\0') {

		if (*s == '$' && *(s - 1) != '\\') {
#ifdef DEBUG
			printf("DEBUG %s:%d toggling inmath; rest of string is \"%s\"\n",__FILE__,__LINE__,s);
#endif
			inmath = (inmath ? false : true);
			s++;
			continue;
		}


		if (inmath) {
			if (*s == '^')
				used_supers = true;
			else if (*s == '_')
				used_subs = true;
			else if (*s == '{')
				;
			else if (*s == '}')
				;
			else if (*s == '\\') {

				if (*(s + 1) == ',') {

					*w += gr_charwidth_cm((int)'M', CurrentFont.id, CurrentFont.size_pt) / 6.0;
					s += 1;
				} else if (*(s + 1) == '!') {

					*w -= gr_charwidth_cm((int)'M', CurrentFont.id, CurrentFont.size_pt) / 6.0;
					s += 1;
				} else {
                                        int inc;
					int symbol_index = symbol_in_math(s, &inc);
					if (symbol_index > -1) {
						gr_fontID oldfontID = CurrentFont.id;
						s += inc;

                                                *w += gr_charwidth_cm('m', gr_font_Symbol, CurrentFont.size_pt);
						CurrentFont.id = oldfontID;
					} else {

						*w += gr_charwidth_cm('\\', CurrentFont.id, CurrentFont.size_pt);
					}
				}
			} else {


				*w += gr_charwidth_cm((int) *s, CurrentFont.id, CurrentFont.size_pt);
			}
		} else {

			*w += gr_charwidth_cm((int) *s, CurrentFont.id, CurrentFont.size_pt);
		}
		s++;
	}

	*a = gr_currentCapHeight_cm() * (1 + (used_supers ? 1 : 0) *
					 (SuperSize + SuperMoveUp - 1));
#if 0
	*d = gr_currentCapHeight_cm() * (1.0 + 0.5 * (int) used_subs);
#endif
	*d = gr_current_descender() * (1 + (used_subs ? 1.0 : 0.0) *
				       (SubSize + SubMoveDown - 1));
#ifdef DEBUG
	printf("DEBUG %s:%d gr_stringwidth(s=\"%s\",...) RETURNING w=%f, a=%f d=%f\n", __FILE__,__LINE__,s,*w,*a,*d);
#endif


	CurrentFont.size_pt = oldfontsize_pt;
	_grWritePS = oldWritePS;
}
