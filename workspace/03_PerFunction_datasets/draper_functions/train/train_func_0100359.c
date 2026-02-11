set_max_length(int length)
{
	if (length < 0)
		return;

	max_length = length;

	if (max_length != 0  &&  (int)text.length() > max_length)
	{

		text.erase(max_length, text.length());
		if (cursor_position > (int)text.length())
			cursor_position = text.length();
	}
}
