on_key_up(const CL_InputEvent &key)
{
	if (key.id == CL_KEY_SPACE || key.id == CL_KEY_RETURN)
		sig_activated(get_current_item());
}
