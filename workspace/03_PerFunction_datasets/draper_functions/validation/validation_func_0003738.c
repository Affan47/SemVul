fc_ulp_login ( struct fc_ulp *ulp, const void *param, size_t param_len,
		   int originated ) {
	struct fc_ulp_user *user;
	struct fc_ulp_user *tmp;


	if ( fc_link_ok ( &ulp->link ) &&
	     ( ( ulp->param_len != param_len ) ||
	       ( memcmp ( ulp->param, param, ulp->param_len ) != 0 ) ) ) {
		fc_ulp_logout ( ulp, 0 );
	}


	if ( originated )
		ulp->flags |= FC_ULP_ORIGINATED_LOGIN_OK;
	if ( ! ( ulp->flags & FC_ULP_ORIGINATED_LOGIN_OK ) ) {
		DBGC ( ulp, "FCULP %s/%02x sending extra PRLI to work around "
		       "Linux bug\n",
		       fc_ntoa ( &ulp->peer->port_wwn ), ulp->type );
		fc_link_stop ( &ulp->link );
		fc_link_start ( &ulp->link );
		return 0;
	}


	if ( ! fc_link_ok ( &ulp->link ) ) {


		assert ( ulp->param == NULL );
		assert ( ulp->param_len == 0 );
		ulp->param = malloc ( param_len );
		if ( ! ulp->param ) {
			DBGC ( ulp, "FCULP %s/%02x could not record "
			       "parameters\n",
			       fc_ntoa ( &ulp->peer->port_wwn ), ulp->type );
			return -ENOMEM;
		}
		memcpy ( ulp->param, param, param_len );
		ulp->param_len = param_len;
		DBGC ( ulp, "FCULP %s/%02x logged in with parameters:\n",
		       fc_ntoa ( &ulp->peer->port_wwn ), ulp->type );
		DBGC_HDA ( ulp, 0, ulp->param, ulp->param_len );


		fc_ulp_get ( ulp );
	}


	fc_link_up ( &ulp->link );


	list_for_each_entry_safe ( user, tmp, &ulp->users, list ) {
		fc_ulp_user_get ( user );
		user->examine ( user );
		fc_ulp_user_put ( user );
	}

	return 0;
}
