ldap_int_tls_start ( LDAP *ld, LDAPConn *conn, LDAPURLDesc *srv )
{
	Sockbuf *sb;
	char *host;
	void *ssl;
	int ret, async;
#ifdef LDAP_USE_NON_BLOCKING_TLS
	struct timeval start_time_tv, tv, tv0;
	ber_socket_t	sd = AC_SOCKET_ERROR;
#endif

	if ( !conn )
		return LDAP_PARAM_ERROR;

	sb = conn->lconn_sb;
	if( srv ) {
		host = srv->lud_host;
	} else {
 		host = conn->lconn_server->lud_host;
	}


	if( host == NULL ) {
		host = "localhost";
	}

	(void) tls_init( tls_imp );

#ifdef LDAP_USE_NON_BLOCKING_TLS


	async = LDAP_BOOL_GET( &ld->ld_options, LDAP_BOOL_CONNECT_ASYNC );
	if ( ld->ld_options.ldo_tm_net.tv_sec >= 0 ) {
		if ( !async ) {

			ber_sockbuf_ctrl( sb, LBER_SB_OPT_SET_NONBLOCK, (void*)1 );
		}
		ber_sockbuf_ctrl( sb, LBER_SB_OPT_GET_FD, &sd );
		tv = ld->ld_options.ldo_tm_net;
		tv0 = tv;
#ifdef HAVE_GETTIMEOFDAY
		gettimeofday( &start_time_tv, NULL );
#else
		time( &start_time_tv.tv_sec );
		start_time_tv.tv_usec = 0;
#endif
	}

#endif

	ld->ld_errno = LDAP_SUCCESS;
	ret = ldap_int_tls_connect( ld, conn, host );


	while ( ret > 0 ) {
#ifdef LDAP_USE_NON_BLOCKING_TLS
		if ( async ) {
			struct timeval curr_time_tv, delta_tv;
			int wr=0;

			if ( sb->sb_trans_needs_read ) {
				wr=0;
			} else if ( sb->sb_trans_needs_write ) {
				wr=1;
			}
			Debug( LDAP_DEBUG_TRACE, "ldap_int_tls_start: ldap_int_tls_connect needs %s\n",
					wr ? "write": "read", 0, 0 );


#ifdef HAVE_GETTIMEOFDAY
			gettimeofday( &curr_time_tv, NULL );
#else
			time( &curr_time_tv.tv_sec );
			curr_time_tv.tv_usec = 0;
#endif


			delta_tv.tv_sec = curr_time_tv.tv_sec - start_time_tv.tv_sec;
			delta_tv.tv_usec = curr_time_tv.tv_usec - start_time_tv.tv_usec;
			if ( delta_tv.tv_usec < 0 ) {
				delta_tv.tv_sec--;
				delta_tv.tv_usec += 1000000;
			}


			if ( ( tv0.tv_sec < delta_tv.tv_sec ) ||
				 ( ( tv0.tv_sec == delta_tv.tv_sec ) &&
				   ( tv0.tv_usec < delta_tv.tv_usec ) ) )
			{
				ret = -1;
				ld->ld_errno = LDAP_TIMEOUT;
				break;
			}

			tv0.tv_sec -= delta_tv.tv_sec;
			tv0.tv_usec -= delta_tv.tv_usec;
			if ( tv0.tv_usec < 0 ) {
				tv0.tv_sec--;
				tv0.tv_usec += 1000000;
			}
			start_time_tv.tv_sec = curr_time_tv.tv_sec;
			start_time_tv.tv_usec = curr_time_tv.tv_usec;
			tv = tv0;
			Debug( LDAP_DEBUG_TRACE, "ldap_int_tls_start: ld %p %ld s %ld us to go\n",
				(void *)ld, (long) tv.tv_sec, (long) tv.tv_usec );
			ret = ldap_int_poll( ld, sd, &tv, wr);
			if ( ret < 0 ) {
				ld->ld_errno = LDAP_TIMEOUT;
				break;
			}
		}
#endif
		ret = ldap_int_tls_connect( ld, conn, host );
	}

	if ( ret < 0 ) {
		if ( ld->ld_errno == LDAP_SUCCESS )
			ld->ld_errno = LDAP_CONNECT_ERROR;
		return (ld->ld_errno);
	}

	return LDAP_SUCCESS;
}
