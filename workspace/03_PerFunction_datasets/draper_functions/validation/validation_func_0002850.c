resmux_try ( struct resolv_mux *mux ) {
	struct resolver *resolver = mux->resolver;
	int rc;

	DBGC ( mux, "RESOLV %p trying method %s\n", mux, resolver->name );

	if ( ( rc = resolver->resolv ( &mux->child, mux->name,
				       &mux->sa ) ) != 0 ) {
		DBGC ( mux, "RESOLV %p could not use method %s: %s\n",
		       mux, resolver->name, strerror ( rc ) );
		return rc;
	}

	return 0;
}
