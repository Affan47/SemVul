check_modules_dir(GF_Config *cfg)
{
	char path[GF_MAX_PATH];
	const char *opt;

	if ( get_default_install_path(path, GF_PATH_MODULES) ) {
#if defined(__DARWIN__) || defined(__APPLE__)
		opt = gf_cfg_get_key(cfg, "General", "ModulesDirectory");
		if (!opt || strcmp(opt, path)) gf_cfg_set_key(cfg, "General", "ModulesDirectory", path);
#endif
	}


	if (gf_cfg_get_key(cfg, "General", "StartupFile")==NULL) return;

	if ( get_default_install_path(path, GF_PATH_GUI) ) {
		opt = gf_cfg_get_key(cfg, "General", "StartupFile");
		if (strstr(opt, "gui.bt") && strcmp(opt, path)) {
#if defined(_WIN32_WCE) || defined(WIN32)
			strcat(path, "\\gui.bt");
#else
			strcat(path, "/gui.bt");
#endif
			gf_cfg_set_key(cfg, "General", "StartupFile", path);
		}
	}
}
