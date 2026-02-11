setup_alarm (ECalBackendContacts *cbc,
             ECalComponent *comp)
{
	ECalComponentAlarm *alarm;
	ECalComponentAlarmTrigger trigger;
	ECalComponentText summary;

	g_return_if_fail (cbc != NULL);

	if (!comp || cbc->priv->alarm_interval == -1) {
		gchar *str;

		if (cbc->priv->alarm_interval == -1) {

			cbc->priv->notifyid = g_signal_connect (cbc->priv->settings,
				"changed", G_CALLBACK (alarm_config_changed_cb), cbc);
		}

		cbc->priv->alarm_enabled = g_settings_get_boolean (cbc->priv->settings, BA_CONF_ENABLED);
		cbc->priv->alarm_interval = g_settings_get_int (cbc->priv->settings, BA_CONF_INTERVAL);

		str = g_settings_get_string (cbc->priv->settings, BA_CONF_UNITS);
		if (str && !strcmp (str, "days"))
			cbc->priv->alarm_units = CAL_DAYS;
		else if (str && !strcmp (str, "hours"))
			cbc->priv->alarm_units = CAL_HOURS;
		else
			cbc->priv->alarm_units = CAL_MINUTES;

		g_free (str);

		if (cbc->priv->alarm_interval <= 0)
			cbc->priv->alarm_interval = 1;

		if (!comp)
			return;
	}


	e_cal_component_remove_all_alarms (comp);


	if (!cbc->priv->alarm_enabled)
		return;

	alarm = e_cal_component_alarm_new ();
	e_cal_component_get_summary (comp, &summary);
	e_cal_component_alarm_set_description (alarm, &summary);
	e_cal_component_alarm_set_action (alarm, E_CAL_COMPONENT_ALARM_DISPLAY);

	trigger.type = E_CAL_COMPONENT_ALARM_TRIGGER_RELATIVE_START;

	memset (&trigger.u.rel_duration, 0, sizeof (trigger.u.rel_duration));

	trigger.u.rel_duration.is_neg = TRUE;

	switch (cbc->priv->alarm_units) {
	case CAL_MINUTES:
		trigger.u.rel_duration.minutes = cbc->priv->alarm_interval;
		break;

	case CAL_HOURS:
		trigger.u.rel_duration.hours = cbc->priv->alarm_interval;
		break;

	case CAL_DAYS:
		trigger.u.rel_duration.days = cbc->priv->alarm_interval;
		break;

	default:
		g_warning ("%s: wrong units %d\n", G_STRFUNC, cbc->priv->alarm_units);
		e_cal_component_alarm_free (alarm);
		return;
	}

	e_cal_component_alarm_set_trigger (alarm, trigger);
	e_cal_component_add_alarm (comp, alarm);
	e_cal_component_alarm_free (alarm);
}
