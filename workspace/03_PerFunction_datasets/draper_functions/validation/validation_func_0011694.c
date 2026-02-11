create_post_context(int flags, char *file_name)
{
    PostContext	*context;
    char	*charset;

    n_post_contexts++;
    charset = res_default_charset();
    if (!charset)
	charset = "iso-8859-1";
    if (!(flags & POST))
	flags |= ORIG_MAIL;

    context = (PostContext *)XtMalloc(sizeof *context);
    context->file_name     = XtNewString(file_name);
    context->art	   = NULL;
    context->charset	   = XtNewString(charset);
    context->line          = 0;
    context->n_attachments = 0;
    context->flags         = flags;
    context->busy          = True;
    context->has_8bit      = False;
    context->widgets       = NULL;
    context->attachments   = NULL;
    context->q_str         = res_quote_string();
    context->qq_str        = res_quote_quote_string();

    return context;
}
