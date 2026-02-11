cl5CreateReplayIteratorEx (Private_Repl_Protocol *prp, const RUV *consumerRuv,
                             CL5ReplayIterator **iterator,	ReplicaId consumerRID )
{
	int rc;
	Object *replica;
	Object *obj = NULL;

	replica = prp->replica_object;
	if (replica == NULL || consumerRuv == NULL || iterator == NULL)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
						"cl5CreateReplayIteratorEx: invalid parameter\n");
		return CL5_BAD_DATA;
	}

    *iterator = NULL;

	if (s_cl5Desc.dbState == CL5_STATE_NONE)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
						"cl5CreateReplayIteratorEx: changelog is not initialized\n");
		return CL5_BAD_STATE;
	}


	rc = _cl5AddThread ();
	if (rc != CL5_SUCCESS ) return rc;


	rc = _cl5GetDBFile (replica, &obj);
	if (rc == CL5_SUCCESS && obj)
	{


		rc = _cl5PositionCursorForReplay (consumerRID, consumerRuv, replica, obj, iterator);
	}
	else
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
						"cl5CreateReplayIteratorEx: could not find DB object for replica\n");
	}

	if (rc != CL5_SUCCESS)
	{
		if (obj) object_release (obj);


		_cl5RemoveThread ();
	}

	return rc;
}
