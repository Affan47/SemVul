PrintGlue(GlueRec g)
{
    if (g.order == 0 || g.value != 1.0)
	printf ("%g", g.value);
    if (g.order > 0)
    {
	printf (" inf");
	if (g.order > 1)
	    printf (" %d", g.order);
    }
}
