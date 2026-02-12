imapx_server_constructed (GObject *object)
{
	CamelIMAPXServer *server;


	G_OBJECT_CLASS (camel_imapx_server_parent_class)->constructed (object);

	server = CAMEL_IMAPX_SERVER (object);
	server->priv->tagprefix = 'Z';
}
