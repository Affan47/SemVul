_copyCreateSchemaStmt(const CreateSchemaStmt *from)
{
	CreateSchemaStmt *newnode = makeNode(CreateSchemaStmt);

	COPY_STRING_FIELD(schemaname);
	COPY_NODE_FIELD(authrole);
	COPY_NODE_FIELD(schemaElts);
	COPY_SCALAR_FIELD(if_not_exists);

	return newnode;
}
