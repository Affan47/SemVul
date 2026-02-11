channel_broadcast( ServerChannel *channel, int len, char *data )
{
    int urgent = 0;
    ServerUser *user;


    if ( data[0] == MSG_ERROR ||
         data[0] == MSG_ADD_USER || data[0] == MSG_REMOVE_USER ||
         data[0] == MSG_SET_COMM_DELAY )
        urgent = 1;


    list_reset( channel->users );
    while ( ( user = list_next( channel->users ) ) )
        if ( !user->no_comm )
        if ( urgent || !user->hidden )
            socket_transmit( &user->socket, CODE_BLUE, len, data );
}
