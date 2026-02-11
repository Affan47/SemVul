readDDS(OCstate* state, OCtree* tree)
{
    int stat;
    long lastmodified = -1;


    ocurisetconstraints(state->uri,tree->constraint);

ocset_user_password(state);

    stat = readpacket(state->curl,state->uri,state->packet,OCDDS,
			&lastmodified);
    if(stat == OC_NOERR) state->ddslastmodified = lastmodified;

    return stat;
}
