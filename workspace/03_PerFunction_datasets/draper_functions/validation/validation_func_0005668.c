color_equal (const GdkRGBA *color_a, const GnmColor *color_gb)
{
	if (color_gb == NULL)
		return color_a == NULL;

	return color_a && GO_COLOR_FROM_GDK_RGBA (*color_a) == color_gb->go_color;
}
