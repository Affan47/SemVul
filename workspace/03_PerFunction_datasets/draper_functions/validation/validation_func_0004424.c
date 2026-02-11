CompareBufferToPlayerNames
  ( const tString & nameRaw,
    int & num_matches,
    ePlayerNetID * requester,
    SE_NameGetter GetName,
    SE_NameFilter Filter,
    SE_NameHider Hider )
{
    num_matches = 0;
    ePlayerNetID * match = 0;


    tString name = (*Filter)( nameRaw );


    for ( int a = se_PlayerNetIDs.Len()-1; a>=0; --a ) {
        ePlayerNetID* toMessage = se_PlayerNetIDs(a);

        if ( (*Hider)( toMessage, requester ) )
        {
            continue;
        }

        tString playerName = (*Filter)( (toMessage->*GetName)() );


        if ( playerName == name )
        {
            num_matches = 1;
            return toMessage;
        }

        if ( Contains(name, playerName)) {
            match= toMessage;
            num_matches+=1;
        }
    }


    return match;
}
