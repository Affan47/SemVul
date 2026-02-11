merge( ihigh, ilow, jhigh, jlow )
  {
    register int  ahigh, alow;

    if( strength( ihigh ) > strength( jhigh ) )
	ahigh = ihigh;
    else if( strength( ihigh ) < strength( jhigh ) )
	ahigh = jhigh;
    else if( ihigh < jhigh )
	ahigh = ihigh;
    else
	ahigh = jhigh;

    if( strength( ilow ) > strength( jlow ) )
	alow = ilow;
    else if( strength( ilow ) < strength( jlow ) )
	alow = jlow;
    else if( ilow > jlow )
	alow = ilow;
    else
	alow = jlow;

    return( pinterval( ahigh, alow ) );
  }
