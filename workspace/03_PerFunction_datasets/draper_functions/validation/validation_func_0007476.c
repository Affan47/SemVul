out_site(struct Site *s)
{
    if (!triangulate & plot & !debug)
	circle(s->coord.x, s->coord.y, cradius);


    return 0;
}
