cpufreq_selector_service_set_frequency (CPUFreqSelectorService *service,
					guint                   cpu,
					guint                   frequency,
					DBusGMethodInvocation  *context)
{
	CPUFreqSelector *selector;
	GError          *error = NULL;

	reset_killtimer ();

	if (!cpufreq_selector_service_check_policy (service, context, &error)) {
		dbus_g_method_return_error (context, error);
		g_error_free (error);

		return FALSE;
	}

	if (cpu > MAX_CPUS) {
		GError *err;

		err = g_error_new (CPUFREQ_SELECTOR_SERVICE_ERROR,
				   SERVICE_ERROR_DBUS,
				   "Error setting frequency on cpu %d: Invalid cpu",
				   cpu);
		dbus_g_method_return_error (context, err);
		g_error_free (err);

		return FALSE;
	}

	selector = get_selector_for_cpu (service, cpu);
	if (!selector) {
		GError *err;

		err = g_error_new (CPUFREQ_SELECTOR_SERVICE_ERROR,
				   SERVICE_ERROR_DBUS,
				   "Error setting frequency on cpu %d: No cpufreq support",
				   cpu);
		dbus_g_method_return_error (context, err);
		g_error_free (err);

		return FALSE;
	}

	cpufreq_selector_set_frequency (selector, frequency, &error);
	if (error) {
		GError *err;

		err = g_error_new (CPUFREQ_SELECTOR_SERVICE_ERROR,
				   SERVICE_ERROR_DBUS,
				   "Error setting frequency %d on cpu %d: %s",
				   frequency, cpu, error->message);
		dbus_g_method_return_error (context, err);
		g_error_free (err);
		g_error_free (error);

		return FALSE;
	}

	dbus_g_method_return (context);

	return TRUE;
}
