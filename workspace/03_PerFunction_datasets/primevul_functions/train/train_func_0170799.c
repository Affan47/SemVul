char *findFillDflt(node_t * n, char *dflt)
{
    char *color;

    color = late_nnstring(n, N_fillcolor, "");
    if (!color[0]) {

	color = late_nnstring(n, N_color, "");
	if (!color[0]) {
	    color = dflt;
	}
    }
    return color;
}
