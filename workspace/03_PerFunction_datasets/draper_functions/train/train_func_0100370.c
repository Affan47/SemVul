model_set(const char *abbr, const char *rating)
{
	if (!strcmp(abbr, "FOR")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "Fortress %s", rating);
		return;
	}

	if (!strcmp(abbr, "FTC")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "Fortress Telecom %s", rating);
		return;
	}

	if (!strcmp(abbr, "PRO")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "Patriot Pro %s", rating);
		inverted_bypass_bit = 1;
		return;
	}

	if (!strcmp(abbr, "PR2")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "Patriot Pro II %s", rating);
		inverted_bypass_bit = 1;
		return;
	}

	if (!strcmp(abbr, "325")) {
		dstate_setinfo("ups.mfr", "%s", "Sola Australia");
		dstate_setinfo("ups.model", "Sola 325 %s", rating);
		return;
	}

	if (!strcmp(abbr, "520")) {
		dstate_setinfo("ups.mfr", "%s", "Sola Australia");
		dstate_setinfo("ups.model", "Sola 520 %s", rating);
		return;
	}

	if (!strcmp(abbr, "610")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "610 %s", rating);
		return;
	}

	if (!strcmp(abbr, "620")) {
		dstate_setinfo("ups.mfr", "%s", "Sola Australia");
		dstate_setinfo("ups.model", "Sola 620 %s", rating);
		return;
	}

	if (!strcmp(abbr, "AX1")) {
		dstate_setinfo("ups.mfr", "%s", "Best Power");
		dstate_setinfo("ups.model", "Axxium Rackmount %s", rating);
		return;
	}

	dstate_setinfo("ups.mfr", "%s", "Unknown");
	dstate_setinfo("ups.model", "Unknown %s (%s)", abbr, rating);

	printf("Unknown model detected - please report this ID: '%s'\n", abbr);
}
