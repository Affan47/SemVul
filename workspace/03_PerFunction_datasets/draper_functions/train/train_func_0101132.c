iff_get_alpha_value(bool is_bright)
{
	if (is_bright == false)
		return (HUD_COLOR_ALPHA_MAX - iff_bright_delta) * 16;
	else
		return HUD_COLOR_ALPHA_MAX * 16;
}
