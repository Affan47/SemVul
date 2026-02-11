D_parse_color(const char *str, int none_acceptable)
{
    int color;

    color = translate_or_add_color(str);
    if (color == -1)
	G_fatal_error(_("[%s]: No such color"), str);
    if (color == 0 && !none_acceptable)
	G_fatal_error(_("[%s]: No such color"), str);
    return color;
}
