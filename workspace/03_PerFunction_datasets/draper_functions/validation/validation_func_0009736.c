Suspend( int rounds )
{
    if ( rounds < 0 )
    {
        rounds = 0;
    }

    int & suspended = AccessSuspended();

    if ( suspended == rounds )
    {
        return;
    }

    suspended = rounds;

    if ( suspended == 0 )
    {
        sn_ConsoleOut( tOutput( "$player_no_longer_suspended", GetColoredName() ) );
        FindDefaultTeam();
    }
    else
    {
        sn_ConsoleOut( tOutput( "$player_suspended", GetColoredName(), suspended ) );
        SetTeam( NULL );
        if ( Object() && Object()->Alive() )
            Object()->Kill();
    }
}
