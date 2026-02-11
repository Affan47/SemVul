CommandRotate_ (MolComplexS *mol_complexSP, int mol_complexesN,
		    RuntimeS *runtimeSP, ConfigS *configSP, GUIS *guiSP,
		    NearestAtomS *nearest_atomSP, size_t pixelsN,
		    unsigned int *refreshIP, char *stringP)
{
char		*remainderP;
char		tokenA[STRINGSIZE];
int		axisID;
double		rotation_angle;


remainderP = ExtractToken_ (tokenA, STRINGSIZE, stringP, " \t\n");
if (!remainderP)
	{
	strcpy (runtimeSP->messageA, "Axis specification missing!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_NO_AXIS;
	}


if      (strcmp (tokenA, "X") == 0) axisID = 1;
else if (strcmp (tokenA, "Y") == 0) axisID = 2;
else if (strcmp (tokenA, "Z") == 0) axisID = 3;
else
	{
	strcpy (runtimeSP->messageA,
		"Bad axis (only x, y and z are available)!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_BAD_AXIS;
	}


remainderP = ExtractToken_ (tokenA, STRINGSIZE, remainderP, " \t\n");
if (!remainderP)
	{
	strcpy (runtimeSP->messageA, "Rotation angle missing!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_NO_ANGLE;
	}


if (sscanf (tokenA, "%lf", &rotation_angle) != 1)
	{
	strcpy (runtimeSP->messageA, "Rotation angle specification is bad!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_NO_ANGLE;
	}


rotation_angle *= DEG_TO_RAD;


Rotate_ (mol_complexSP, mol_complexesN,
	 runtimeSP, configSP, rotation_angle, axisID);


(*refreshIP)++;
MainRefresh_ (mol_complexSP, mol_complexesN, runtimeSP, configSP, guiSP,
	      nearest_atomSP, pixelsN, *refreshIP);


ControlRefresh_ (mol_complexSP + runtimeSP->default_complexI, configSP, guiSP);


if (guiSP->dockingF) DockingRefresh_ (runtimeSP, guiSP);


return COMMAND_ROTATE;
}
