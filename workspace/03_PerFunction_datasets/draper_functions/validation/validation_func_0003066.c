GetVoter( int ID, bool complain )
{

#ifdef DEDICATED
    if ( ID == 0 )
        return NULL;
#endif


    if ( !se_allowVotingSpectator )
    {
        bool player = false;
        for ( int i = se_PlayerNetIDs.Len()-1; i>=0; --i )
        {
            ePlayerNetID* p = se_PlayerNetIDs(i);
            if ( p->Owner() == ID && p->CurrentTeam() )
                player = true;
        }
        if (!player)
        {
            if ( complain )
            {
                tOutput message("$vote_disabled_spectator");
                sn_ConsoleOut( message, ID );
            }
            return NULL;
        }
    }


    nMachine & machine = nMachine::GetMachine( ID );

    return GetVoter( machine );
}
