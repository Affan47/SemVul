gtksettings_gtk_settings_set_property_value(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj settings_scm;
  GtkSettings* settings;
  ScmObj name_scm;
  const gchar * name;
  ScmObj svalue_scm;
  GtkSettingsValue* svalue;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-settings-set-property-value");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  settings_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_SETTINGS_P(settings_scm)) Scm_Error("<gtk-settings> required, but got %S", settings_scm);
  settings = SCM_GTK_SETTINGS(settings_scm);
  name_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(name_scm)) Scm_Error("<const-gchar*> required, but got %S", name_scm);
  name = CONST_GCHAR_PTR(name_scm);
  svalue_scm = SCM_SUBRARGS[2];
  if (!SCM_GTK_SETTINGS_VALUE_P(svalue_scm)) Scm_Error("<gtk-settings-value> required, but got %S", svalue_scm);
  svalue = SCM_GTK_SETTINGS_VALUE(svalue_scm);
  {
gtk_settings_set_property_value(settings, name, svalue);
SCM_RETURN(SCM_UNDEFINED);
  }
}
