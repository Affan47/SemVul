makeDFA( void )
{
    if( !SW_Quiet ){
	fprintf( stderr, "Now making deterministic finite automaton" );
	NoNewLine = 1;
    }
    r_makeDFA( FAlist );
    if( !SW_Quiet ){
	fprintf( stderr, "\rNow making deterministic finite automaton[%d/%d] \n", FAprocessed, FAtotal );
	if( FAtotal != FAprocessed ){
	    fprintf( stderr, "* %d released FA nodes are left on isolated loop\n", FAtotal - FAprocessed );
	}
	NoNewLine = 0;
    }


    FAtotal = FAprocessed;
    if( SW_Verbose ){
	verboseMes( "** traversing efficiency ( success/total )" );
	verboseMes( "r_makeDFA:     %d/%d(%d%%)",
		DFAtravSuccess, DFAtravTotal, 100*DFAtravSuccess/DFAtravTotal);
    }
    newLineAdjust();
    freeFAlist( GroupList );
}
