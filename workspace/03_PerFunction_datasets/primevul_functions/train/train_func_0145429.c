int main(int argc, char *argv[]) {
	SERVER* serve;
	GArray* servers;

	if (sizeof( struct nbd_request )!=28) {
		fprintf(stderr,"Bad size of structure. Alignment problems?\n");
		exit(-1) ;
	}

	logging();
	serve=cmdline(argc, argv);
	servers=g_array_new(TRUE, FALSE, sizeof(SERVER*));

	if (!(serve->port)) {
	  	CLIENT *client;
#ifndef ISSERVER


          	close(1);
          	close(2);
          	open("/dev/null", O_WRONLY);
          	open("/dev/null", O_WRONLY);
#endif
		client=g_malloc(sizeof(CLIENT));
		client->server=serve;
		client->net=0;
		client->exportsize=OFFT_MAX;
          	set_peername(0,client);
          	serveconnection(client);
          	return 0;
        }
	daemonize(serve);
	setup_serve(serve);
	serveloop(serve);
	return 0 ;
}
