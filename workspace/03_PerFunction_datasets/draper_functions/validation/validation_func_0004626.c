sokoban_detect()
{
	register int x, y;
	register struct trap *ttmp;
	register struct obj *obj;


	for (x = 1; x < COLNO; x++)
	    for (y = 0; y < ROWNO; y++) {
	    	levl[x][y].seenv = SVALL;
	    	levl[x][y].waslit = TRUE;
	    	map_background(x, y, 1);
	    	for (obj = level.objects[x][y]; obj; obj = obj->nexthere)
	    	    if (obj->otyp == BOULDER)
	    	    	map_object(obj, 1);
	    }


	for (ttmp = ftrap; ttmp; ttmp = ttmp->ntrap) {
	    ttmp->tseen = 1;
	    map_trap(ttmp, 1);
	}
}
