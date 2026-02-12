static void get_connector_control_name(struct usb_mixer_interface *mixer,
				       struct usb_audio_term *term,
				       bool is_input, char *name, int name_size)
{
	int name_len = get_term_name(mixer->chip, term, name, name_size, 0);

	if (name_len == 0)
		strlcpy(name, "Unknown", name_size);


	if (is_input)
		strlcat(name, " - Input Jack", name_size);
	else
		strlcat(name, " - Output Jack", name_size);
}
