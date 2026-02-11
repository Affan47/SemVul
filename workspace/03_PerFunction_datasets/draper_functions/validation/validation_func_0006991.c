PutRange(CharSet *s) {
	for (CharSet::Range *r = s->head; r != NULL; r = r->next) {
		if (r->from == r->to) {
			wchar_t *from = Ch((wchar_t) r->from);
			fwprintf(gen, L"ch == %ls", from);
			delete [] from;
		} else if (r->from == 0) {
			wchar_t *to = Ch((wchar_t) r->to);
			fwprintf(gen, L"ch <= %ls", to);
			delete [] to;
		} else {
			wchar_t *from = Ch((wchar_t) r->from);
			wchar_t *to = Ch((wchar_t) r->to);
			fwprintf(gen, L"(ch >= %ls && ch <= %ls)", from, to);
			delete [] from; delete [] to;
		}
		if (r->next != NULL) fwprintf(gen, L" || ");
	}
}
