imap_store_msg( store_t *gctx, msg_data_t *data, int to_trash,
                int (*cb)( int sts, int uid, void *aux ), void *aux )
{
	imap_store_t *ctx = (imap_store_t *)gctx;
	struct imap_cmd *cmd = new_imap_cmd();
	const char *prefix, *box;
	int ret, d, uid;
	char flagstr[128];

	d = 0;
	if (data->flags) {
		d = imap_make_flags( data->flags, flagstr );
		flagstr[d++] = ' ';
	}
	flagstr[d] = 0;

	cmd->param.data_len = data->len;
	cmd->param.data = data->data;
	cmd->param.aux = &uid;
	uid = -2;

	if (to_trash) {
		box = gctx->conf->trash;
		prefix = ctx->prefix;
		cmd->param.create = 1;
		if (ctx->trashnc)
			ctx->caps = ctx->rcaps & ~(1 << LITERALPLUS);
	} else {
		box = gctx->name;
		prefix = !strcmp( box, "INBOX" ) ? "" : ctx->prefix;
		cmd->param.create = (gctx->opts & OPEN_CREATE) != 0;


	}
	ret = imap_exec_m( ctx, cmd, "APPEND \"%s%s\" %s", prefix, box, flagstr );
	ctx->caps = ctx->rcaps;
	if (ret != DRV_OK)
		return cb( ret, -1, aux );
	if (to_trash)
		ctx->trashnc = 0;
	else {

	}

	return cb( DRV_OK, uid, aux );
}
