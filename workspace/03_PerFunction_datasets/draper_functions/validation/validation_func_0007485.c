save_msg_stream(CONTEXT_S *context, char *folder, int *we_opened)
{
    char	tmp[MAILTMPLEN];
    MAILSTREAM *save_stream = NULL;

    if(IS_REMOTE(context_apply(tmp, context, folder, sizeof(tmp)))
       && !(save_stream = sp_stream_get(tmp, SP_MATCH))
       && !(save_stream = sp_stream_get(tmp, SP_SAME))){
	if((save_stream = context_open(context, NULL, folder,
				      OP_HALFOPEN | SP_USEPOOL | SP_TEMPUSE,
				      NULL)) != NULL)
	  *we_opened = 1;
    }

    return(save_stream);
}
