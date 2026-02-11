que_node_print_info(

	que_node_t*	node)
{
	ulint		type;
	const char*	str;

	type = que_node_get_type(node);

	if (type == QUE_NODE_SELECT) {
		str = "SELECT";
	} else if (type == QUE_NODE_INSERT) {
		str = "INSERT";
	} else if (type == QUE_NODE_UPDATE) {
		str = "UPDATE";
	} else if (type == QUE_NODE_WHILE) {
		str = "WHILE";
	} else if (type == QUE_NODE_ASSIGNMENT) {
		str = "ASSIGNMENT";
	} else if (type == QUE_NODE_IF) {
		str = "IF";
	} else if (type == QUE_NODE_FETCH) {
		str = "FETCH";
	} else if (type == QUE_NODE_OPEN) {
		str = "OPEN";
	} else if (type == QUE_NODE_PROC) {
		str = "STORED PROCEDURE";
	} else if (type == QUE_NODE_FUNC) {
		str = "FUNCTION";
	} else if (type == QUE_NODE_LOCK) {
		str = "LOCK";
	} else if (type == QUE_NODE_THR) {
		str = "QUERY THREAD";
	} else if (type == QUE_NODE_COMMIT) {
		str = "COMMIT";
	} else if (type == QUE_NODE_UNDO) {
		str = "UNDO ROW";
	} else if (type == QUE_NODE_PURGE) {
		str = "PURGE ROW";
	} else if (type == QUE_NODE_ROLLBACK) {
		str = "ROLLBACK";
	} else if (type == QUE_NODE_CREATE_TABLE) {
		str = "CREATE TABLE";
	} else if (type == QUE_NODE_CREATE_INDEX) {
		str = "CREATE INDEX";
	} else if (type == QUE_NODE_FOR) {
		str = "FOR LOOP";
	} else if (type == QUE_NODE_RETURN) {
		str = "RETURN";
	} else if (type == QUE_NODE_EXIT) {
		str = "EXIT";
	} else {
		str = "UNKNOWN NODE TYPE";
	}

	fprintf(stderr, "Node type %lu: %s, address %p\n",
		(ulong) type, str, (void*) node);
}
