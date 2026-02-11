namtoad( name, destdots )
    char *name, *destdots;
{
    struct in_addr  sbuf;
    char *res;
    struct  hostent  *komvos;

    res = NULL;
    if  ( ( komvos = gethostbyname( name ) ) == NULL ) {
        printf("Host under the name *%s* was not found \n", name);
        return(INIT_ER);
    }
    memcpy( (char *)&sbuf, komvos->h_addr, komvos->h_length );
    memset( (char *)destdots, 0, 128 );
    if ( ( res = inet_ntoa( sbuf ) ) == NULL ) {
        printf("Name *%s* couldn't be converted \n", name );
        perror(" ");
        return(INIT_ER);
    } else {
        strcpy( destdots, res );
    }
}
