make_entry (EntriesView& view, const ustring& name,
	const ustring& format) const throw ()
{
	if (always || has_value ())
		view.entry (name, get_string (format), get_tip ());
}
