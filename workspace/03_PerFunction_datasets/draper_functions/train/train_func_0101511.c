JCnewConn(void)
{
	JABBER_Conn *jnew = NULL;


	jnew = calloc(1, sizeof(JABBER_Conn));
	jnew->next = Connections;
	eb_debug(DBG_JBR, "JCnewConn: %p\n", jnew);
	Connections = jnew;
	jnew->state = JCONN_STATE_OFF;
	return (Connections);
}
