Cvar_Increase_f (void)
{
	cvar_t	*var;
	char	val[32];
	float	value;

	if (Cmd_Argc() < 2) {
		Com_Printf ("Usage: %s <cvar> [value]\n", Cmd_Argv(0));
		return;
	}

	var = Cvar_FindVar(Cmd_Argv(1));
	if (!var) {
		Com_Printf ("Unknown cvar '%s'\n", Cmd_Argv(1));
		return;
	}

	if(!Q_IsNumeric(var->string)) {
		Com_Printf( "\"%s\" is \"%s\", can't increment\n", var->name, var->string );
		return;
	}

	if(Cmd_Argc() > 2) {
		if(!Q_IsNumeric(Cmd_Argv(2))) {
			Com_Printf( "\"%s\" is not numeric\n", Cmd_Argv(2));
			return;
		}
		value = (float)atof(Cmd_Argv(2));
	}
	else {
		value = 1.0f;
	}

	if(!Q_stricmp(Cmd_Argv(0), "dec"))
		value = var->value - value;
	else
		value = var->value + value;

	if (value == (int)value)
		Com_sprintf (val, sizeof(val), "%i", (int)value);
	else
		Com_sprintf (val, sizeof(val), "%g", value);

	Cvar_SetByVar(var, val, false);
}
