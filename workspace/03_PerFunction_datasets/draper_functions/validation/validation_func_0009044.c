setupModel (struct state *st)
{
    int c;
    int r;

    int leftX;
    int topY;

    if (st->tileSize > (st->windowWidth / 2))
    {
	st->tileSize = st->windowWidth / 2;
    }

    if (st->tileSize > (st->windowHeight / 2))
    {
	st->tileSize = st->windowHeight / 2;
    }

    st->columns = st->tileSize ? st->windowWidth / st->tileSize : 0;
    st->rows = st->tileSize ? st->windowHeight / st->tileSize : 0;

    if ((st->maxColumns != 0) && (st->columns > st->maxColumns))
    {
	st->columns = st->maxColumns;
    }

    if ((st->maxRows != 0) && (st->rows > st->maxRows))
    {
	st->rows = st->maxRows;
    }

    st->tileCount = st->rows * st->columns;

    leftX = (st->windowWidth - (st->columns * st->tileSize) + st->tileSize) / 2;
    topY = (st->windowHeight - (st->rows * st->tileSize) + st->tileSize) / 2;

    st->tiles = calloc (st->tileCount, sizeof (Tile));
    st->sortedTiles = calloc (st->tileCount, sizeof (Tile *));

    for (r = 0; r < st->rows; r++)
    {
	for (c = 0; c < st->columns; c++)
	{
	    Tile *t = TILE_AT (c, r);
	    t->x = leftX + c * st->tileSize;
	    t->y = topY + r * st->tileSize;
	    st->sortedTiles[c + r * st->columns] = t;
	}
    }

    randomizeEverything (st);
}
