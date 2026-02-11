xkl_xmm_activate_config_rec(XklEngine * engine, const XklConfigRec * data)
{
	gboolean rv;
	rv = xkl_config_rec_set_to_root_window_property(data,
							xkl_engine_priv
							(engine,
							 base_config_atom),
							xkl_engine_backend
							(engine, XklXmm,
							 current_rules),
							engine);
	if (rv)
		xkl_xmm_lock_group(engine, 0);
	return rv;
}
