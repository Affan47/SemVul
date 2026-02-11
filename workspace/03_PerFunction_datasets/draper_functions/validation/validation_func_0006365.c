db_mod_del(db_api_arg_t *key)
{
struct	db_api_module	*mod = db_api_first;
int			aflag = 0;

    if ( !key ) return(DB_API_RES_CODE_ERR);
    while ( mod ) {
	if ( mod->db_api_del ) (mod->db_api_del)(key, &aflag);
	if ( aflag == MOD_AFLAG_BRK )
	    return(key->flags);
	mod = (struct db_api_module*)((struct general_module*)mod)->next;
    }
    return(DB_API_RES_CODE_NOTFOUND);
}
