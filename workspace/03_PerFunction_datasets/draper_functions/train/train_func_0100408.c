view_char(struct view *view, position_t offset, position_t *next)
{
	position_t next0;
	Unicode_t ch = view_unicode(view, offset, &next0);

	if (!next)
		return ch;
	*next = next0;
	if (IS_FOLDED(ch)) {
		size_t fbytes = FOLDED_BYTES(ch);
		position_t next2;
		if (view_unicode(view, next0 + fbytes, &next2) ==
		    FOLD_END + fbytes)
			*next = next2;
	}
	return ch;
}
