protocol_send_raw_params( proto *p, const char *args ) {
	char *aand, *aeq, *asep;
	while( true ) {
		aand = strchr(args,'&');
		if( aand == NULL ) {
			asep = strchr(args,';');
			aand = asep;
		} else {
			asep = strchr(args,';');
			if( asep != NULL && asep < aand )
				aand = asep;
		}
		if( aand != NULL )
			*aand = 0;
		aeq = strchr(args,'=');
		if( aeq != NULL ) {
			*aeq = 0;
			proto_send_decode(p,CODE_PARAM_KEY,args,(int)(aeq-args));
			proto_send_decode(p,CODE_PARAM_VALUE,aeq+1,(int)strlen(aeq+1));
			*aeq = '=';
		}
		if( aand == NULL )
			break;
		*aand = (aand == asep)?';':'&';
		args = aand+1;
	}
}
