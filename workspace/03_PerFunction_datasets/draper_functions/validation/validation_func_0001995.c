plD_state_hpgl(PLStream *pls, PLINT op)
{


    static int hcolmap[16] = { 6,1,2,3,4,5,6,7,8,4,4,8,8,5,5,7 };

    switch (op) {

    case PLSTATE_WIDTH:
    case PLSTATE_COLOR0:{
	int width =
	    (pls->width < MIN_WIDTH) ? DEF_WIDTH :
	    (pls->width > MAX_WIDTH) ? MAX_WIDTH : pls->width;

	if ( pls->icol0 < 0 || pls->icol0 > 15)
	    fputs( "\nInvalid pen selection.", stderr );
	else
	    fprintf( OF, "SP%d %d\n", hcolmap[pls->icol0], width );

	break;
    }
    case PLSTATE_COLOR1:
	break;
    }
}
