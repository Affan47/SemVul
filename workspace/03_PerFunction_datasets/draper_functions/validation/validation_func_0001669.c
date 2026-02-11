UpdateSuspensions() {
    for ( int i = se_PlayerNetIDs.Len()-1; i>=0; --i )
    {
        ePlayerNetID* p = se_PlayerNetIDs(i);

        int suspended = p->GetSuspended();


        if ( suspended > 0 )
        {
            if ( p->CurrentTeam() && !p->NextTeam() )
            {
                p->UpdateTeam();
            }
            else
            {
                p->Suspend( suspended - 1 );
            }
        }
    }
}
