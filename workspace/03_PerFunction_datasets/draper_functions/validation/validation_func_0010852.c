cl5Open (const char *dir, const CL5DBConfig *config)
{
	int rc;

	if (dir == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl, "cl5Open: null directory\n");
		return CL5_BAD_DATA;
	}

	if (s_cl5Desc.dbState == CL5_STATE_NONE)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
						"cl5Open: changelog is not initialized\n");
		return CL5_BAD_STATE;
	}


	slapi_rwlock_wrlock (s_cl5Desc.stLock);


	if (s_cl5Desc.dbState == CL5_STATE_OPEN)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
					"cl5Open: changelog already opened; request ignored\n");
		rc = CL5_SUCCESS;
		goto done;
	}
	else if (s_cl5Desc.dbState != CL5_STATE_CLOSED)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
						"cl5Open: invalid state - %d\n", s_cl5Desc.dbState);
		rc = CL5_BAD_STATE;
		goto done;
	}

	rc = _cl5Open (dir, config, CL5_OPEN_NORMAL);
	if (rc != CL5_SUCCESS)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
						"cl5Open: failed to open changelog\n");
		goto done;
	}


	rc = _cl5DispatchDBThreads ();
	if (rc != CL5_SUCCESS)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
						"cl5Open: failed to start database monitoring threads\n");

		_cl5Close ();
	}
	else
	{
		s_cl5Desc.dbState = CL5_STATE_OPEN;
		clcache_set_config();


		rc = clcrypt_init(config, &s_cl5Desc.clcrypt_handle);
	}

done:
	slapi_rwlock_unlock (s_cl5Desc.stLock);

	return rc;
}
