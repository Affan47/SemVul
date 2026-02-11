srv_connect_silent(int client_so, struct url *url, struct request *rq)
{
int 			server_so = -1, r;
struct	sockaddr_in 	server_sa;
    int			flags = 0;

    r = check_redir_connect(&server_so, rq, &flags);
    if ( server_so != -1 )
	return(server_so);
    if ( r == MOD_CODE_ERR ) {
	return(-1);
    }

    server_so = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( server_so == -1 ) {
	return(-1);
    }
    bind_server_so(server_so, rq);
    if ( str_to_sa(url->host, (struct sockaddr*)&server_sa) ) {
	CLOSE(server_so);
	return(-1);
    }
    server_sa.sin_port = htons(url->port);
    r = connect(server_so, (struct sockaddr*)&server_sa, sizeof(server_sa));
    if ( r == -1 ) {
	CLOSE(server_so);
	return(-1);
    }
    return(server_so);
}
