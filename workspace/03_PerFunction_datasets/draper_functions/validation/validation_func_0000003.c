fromAgentItem(const AgentItem &ai)
{
	setJid( ai.jid() );
	setName( ai.name() );

	Identity id;
	id.category = ai.category();
	id.type = ai.type();
	id.name = ai.name();

	Identities idList;
	idList << id;

	setIdentities( idList );

	setFeatures( ai.features() );
}
