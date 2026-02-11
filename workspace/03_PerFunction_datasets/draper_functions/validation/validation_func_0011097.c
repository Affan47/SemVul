ChatDirectedTowardsPlayer( const tString & prefix, int & nameLen ) const
{
    tString possiblePlayer( prefix );


    if ( st_StringEndsWith( possiblePlayer, ": " ) || st_StringEndsWith( possiblePlayer, ", " ) )
        possiblePlayer = possiblePlayer.SubStr( 0, possiblePlayer.Len() - 3 );

    if ( ePlayerNetID::FindPlayerByName( possiblePlayer, 0, false ) )
    {
        nameLen = possiblePlayer.Len();
        return true;
    }

    return false;
}
