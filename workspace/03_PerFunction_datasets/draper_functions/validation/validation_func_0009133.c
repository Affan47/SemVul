graph_cleanup(graph_t *g)
{
    if (GD_drawing(g) && GD_drawing(g)->xdots)
	freeXDot ((xdot*)GD_drawing(g)->xdots);
    if (GD_drawing(g) && GD_drawing(g)->id)
	free (GD_drawing(g)->id);
    free(GD_drawing(g));
    GD_drawing(g) = NULL;
    free_label(GD_label(g));


    agclean(g, AGRAPH,"Agraphinfo_t");
}
