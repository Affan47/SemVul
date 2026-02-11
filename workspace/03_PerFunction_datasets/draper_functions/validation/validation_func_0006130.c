select_alias_prefix (struct multipath * mp)
{
	if (mp->hwe && mp->hwe->alias_prefix) {
		mp->alias_prefix = mp->hwe->alias_prefix;
		condlog(3, "%s: alias_prefix = %s (controller setting)",
			mp->wwid, mp->alias_prefix);
		return;
	}
	if (conf->alias_prefix) {
		mp->alias_prefix = conf->alias_prefix;
		condlog(3, "%s: alias_prefix = %s (config file default)",
			mp->wwid, mp->alias_prefix);
		return;
	}
	mp->alias_prefix = set_default(DEFAULT_ALIAS_PREFIX);
	condlog(3, "%s: alias_prefix = %s (internal default)",
		mp->wwid, mp->alias_prefix);
}
