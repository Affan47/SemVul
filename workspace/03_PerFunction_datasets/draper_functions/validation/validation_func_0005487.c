set_graph_palette (int i, gretlRGB color)
{
    if (i >= 0 && i < N_GP_COLORS) {
	user_color[i] = color;
    } else {
	fprintf(stderr, "Out of bounds color index %d\n", i);
    }
}
