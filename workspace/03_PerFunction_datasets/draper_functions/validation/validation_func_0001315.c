Venn_ (MolComplexS *mol_complexSP, int mol_complexesN,
	   RuntimeS *runtimeSP, ConfigS *configSP, GUIS *guiSP,
	   NearestAtomS *nearest_atomSP, size_t pixelsN,
	   unsigned int *refreshIP, char *stringP)
{
char		*remainderP;
char		tokenA[SHORTSTRINGSIZE];
char		*P;
int		n;
int		residue1I, residue2I;


remainderP = ExtractToken_ (tokenA, STRINGSIZE, stringP, " \t\n");


if (remainderP)
	{

	if (strstr (tokenA, "OFF") == tokenA)
		{

		guiSP->main_window_modeI = 0;


		InitNearest_ (nearest_atomSP, pixelsN);
		*refreshIP = 1;


		(*refreshIP)++;
		MainRefresh_ (mol_complexSP, mol_complexesN,
			      runtimeSP, configSP, guiSP,
			      nearest_atomSP, pixelsN, *refreshIP);


		ControlRefresh_ (mol_complexSP + runtimeSP->default_complexI,
				 configSP, guiSP);


		return COMMAND_VENN;
		}


	else
		{

		P = stringP;
		while ((n = *P++) != '\0')
			{
			if (n == '-') *(P - 1) = ' ';
			}


		if (ExtractTwoIntegers_ (&residue1I, &residue2I, stringP) < 0)
			{
			strcpy (runtimeSP->messageA,
				"Command interpretation failed!");
			runtimeSP->message_length =
						strlen (runtimeSP->messageA);
			return ERROR_VENN;
			}


		if ((residue1I < 1) || (residue2I < residue1I))
			{
			strcpy (runtimeSP->messageA,
				"Bad range (check indices)!");
			runtimeSP->message_length =
						strlen (runtimeSP->messageA);
			return ERROR_VENN;
			}


		runtimeSP->range_startI = residue1I - 1;
		runtimeSP->range_endI   = residue2I - 1;
		}
	}


else
	{
	runtimeSP->range_startI = 0;
	if (runtimeSP->residuesN >= 1)
		{
		runtimeSP->range_endI = (int) runtimeSP->residuesN - 1;
		}
	else
		{
		runtimeSP->range_endI = 0;
		}
	}


guiSP->main_window_modeI = 3;


InitNearest_ (nearest_atomSP, pixelsN);
*refreshIP = 1;


(*refreshIP)++;
MainRefresh_ (mol_complexSP, mol_complexesN,
	      runtimeSP, configSP, guiSP,
	      nearest_atomSP, pixelsN, *refreshIP);


ControlRefresh_ (mol_complexSP + runtimeSP->default_complexI, configSP, guiSP);


return COMMAND_VENN;
}
