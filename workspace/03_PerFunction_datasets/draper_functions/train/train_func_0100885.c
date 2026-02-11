ftp_reply ( struct ftp_request *ftp ) {
	char status_major = ftp->status_text[0];
	char separator = ftp->status_text[3];

	DBGC ( ftp, "FTP %p received status %s\n", ftp, ftp->status_text );


	if ( separator != ' ' )
		return;


	if ( status_major == '1' )
		return;


	if ( ( status_major == '5' ) && ( ftp->state == FTP_SIZE ) ) {
		ftp_next_state ( ftp );
		return;
	}


	if ( ! ( ( status_major == '2' ) ||
		 ( ( status_major == '3' ) && ( ftp->state == FTP_USER ) ) ) ){

		ftp_done ( ftp, -EPROTO );
		return;
	}


	if ( ftp->state == FTP_SIZE ) {
		size_t filesize;
		char *endptr;


		filesize = strtoul ( ftp->filesize, &endptr, 10 );
		if ( *endptr != '\0' ) {
			DBGC ( ftp, "FTP %p invalid SIZE \"%s\"\n",
			       ftp, ftp->filesize );
			ftp_done ( ftp, -EPROTO );
			return;
		}


		DBGC ( ftp, "FTP %p file size is %zd bytes\n", ftp, filesize );
		xfer_seek ( &ftp->xfer, filesize );
		xfer_seek ( &ftp->xfer, 0 );
	}


	if ( ftp->state == FTP_PASV ) {
		char *ptr = ftp->passive_text;
		union {
			struct sockaddr_in sin;
			struct sockaddr sa;
		} sa;
		int rc;

		sa.sin.sin_family = AF_INET;
		ftp_parse_value ( &ptr, ( uint8_t * ) &sa.sin.sin_addr,
				  sizeof ( sa.sin.sin_addr ) );
		ftp_parse_value ( &ptr, ( uint8_t * ) &sa.sin.sin_port,
				  sizeof ( sa.sin.sin_port ) );
		if ( ( rc = xfer_open_socket ( &ftp->data, SOCK_STREAM,
					       &sa.sa, NULL ) ) != 0 ) {
			DBGC ( ftp, "FTP %p could not open data connection\n",
			       ftp );
			ftp_done ( ftp, rc );
			return;
		}
	}


	ftp_next_state ( ftp );

}
