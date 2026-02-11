settings_remove_hash(const char *key, SETTINGS_REC *rec,
				const char *module)
{
	if (strcmp(rec->module, module) == 0) {
		settings_unref(rec, FALSE);
                return TRUE;
	}

        return FALSE;
}
