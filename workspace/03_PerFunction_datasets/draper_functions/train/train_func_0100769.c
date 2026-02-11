view_unfold(struct view *view, position_t offset)
{
	position_t next, next2;
	size_t fbytes;
	Unicode_t ch = view_unicode(view, offset, &next);

	if (ch < FOLD_START || ch >= FOLD_END)
		return -1;
	fbytes = FOLDED_BYTES(ch);
	if (view_unicode(view, next + fbytes, &next2) !=
	    FOLD_END + fbytes)
		return -1;
	view_delete(view, next + fbytes, next2 - (next + fbytes));
	view_delete(view, offset, next - offset);
	view->text->foldings--;
	return offset + fbytes;
}
