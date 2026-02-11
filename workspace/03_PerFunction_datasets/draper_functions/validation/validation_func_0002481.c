SaveSettingsActiveSet(wxString active_set)
{
#if defined(TRACE_ENVVARS)
  Manager::Get()->GetLogManager()->DebugLog(F(_T("SaveSettingsActiveSet")));
#endif

  ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("envvars"));
  if (!cfg)
    return;

  if (active_set.IsEmpty())
    active_set = nsEnvVars::EnvVarsDefault;

  EV_DBGLOG(_T("EnvVars: Saving '%s' as active envvar set to config."), active_set.wx_str());
  cfg->Write(_T("/active_set"), active_set);
}
