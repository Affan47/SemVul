fc_ulp_detach ( struct fc_ulp_user *user ) {
	struct fc_ulp *ulp = user->ulp;


	if ( ! ulp )
		return;


	list_check_contains_entry ( user, &ulp->users, list );


	list_del ( &user->list );
	if ( list_empty ( &ulp->users ) )
		fc_ulp_logout ( ulp, 0 );


	fc_peer_decrement ( ulp->peer );


	user->ulp = NULL;
	fc_ulp_put ( ulp );
}
