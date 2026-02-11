convert_color_channel (guint  src,
                       guint8 alpha)
{
	return (alpha ? ((src << 8) - src) / alpha : 0);
}
