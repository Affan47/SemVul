lookup_cable_names(enum cable_selections selection)
{
	static char *cable_names[] = {
		[short_cable]     = "short",
		[long_cable]      = "long",
		[medium_cable]    = "medium",
		[undefined_cable] = "<undefined, assumed long>"
	};
	return (selection <= undefined_cable) ? cable_names[selection]
					      : cable_names[undefined_cable];
}
