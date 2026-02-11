module_by_name(char *name)
{
struct general_module	*res;
    res = (struct general_module*)log_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)err_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)auth_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)redir_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)output_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)listener_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)headers_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)pre_body_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    res = (struct general_module*)db_api_first;
    while( res ) {
	if ( !strcasecmp(res->name, name) )
	    return(res);
	res = res->next;
    }
    return(res);
}
