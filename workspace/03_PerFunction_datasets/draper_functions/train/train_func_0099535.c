has_writable_extra_pane (NemoView *view)
{
	NemoView *other_view;

	other_view = get_directory_view_of_extra_pane (view);
	if (other_view != NULL) {
		return !nemo_view_is_read_only (other_view);
	}
	return FALSE;
}
