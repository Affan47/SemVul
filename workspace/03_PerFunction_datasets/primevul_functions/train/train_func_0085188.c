BackendRun(Port *port)
{


	MemoryContextSwitchTo(TopMemoryContext);

	PostgresMain(port->database_name, port->user_name);
}
