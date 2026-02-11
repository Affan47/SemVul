CommandBackbone_ (MolComplexS *mol_complexSP, int mol_complexesN,
		      RuntimeS *runtimeSP, ConfigS *configSP, GUIS *guiSP,
		      NearestAtomS *nearest_atomSP, size_t pixelsN,
		      unsigned int *refreshIP, char *stringP)
{
char		*remainderP;
char		tokenA[STRINGSIZE];
int		backbone_styleI;
int		mol_complexI;
MolComplexS	*curr_mol_complexSP;
size_t		c_alphaI, c_alphaN;
BackboneS	*curr_backboneSP;
AtomS		*curr_atomSP;


backbone_styleI = configSP->default_backbone_styleI;


remainderP = ExtractToken_ (tokenA, STRINGSIZE, stringP, " \t\n");


if (remainderP)
	{

	if 	(strstr (tokenA, "OFF") == tokenA) backbone_styleI = -1;
	else if (strcmp (tokenA,   "0") == 0)      backbone_styleI =  0;
	else if (strcmp (tokenA,   "1") == 0)      backbone_styleI =  1;
	else if (strcmp (tokenA,   "2") == 0)      backbone_styleI =  2;
	else if (strcmp (tokenA,   "3") == 0)      backbone_styleI =  3;
	else if (strcmp (tokenA,   "4") == 0)      backbone_styleI =  4;
	else if (strcmp (tokenA,   "5") == 0)      backbone_styleI =  5;
	else
		{
		sprintf (runtimeSP->messageA,
			 "Backbone drawing style \"%s\" not available!",
			 tokenA);
		runtimeSP->message_length = strlen (runtimeSP->messageA);
		return ERROR_BACKBONE;
		}
	}


for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
	{

	curr_mol_complexSP = mol_complexSP + mol_complexI;


	if (curr_mol_complexSP->catchF == 0) continue;


	c_alphaN = curr_mol_complexSP->c_alphaN;


	for (c_alphaI = 0; c_alphaI < c_alphaN; c_alphaI++)
		{

		curr_backboneSP = curr_mol_complexSP->backboneSP + c_alphaI;


		curr_atomSP = curr_mol_complexSP->atomSP +
			      curr_backboneSP->c_alphaI;


		if (curr_atomSP->selectedF == 0) continue;


		curr_backboneSP->backbone_styleI = backbone_styleI;
		}
	}


if (backbone_styleI == -1)
	{

	ShowNoRefresh_ (mol_complexSP, mol_complexesN);


	HideBackbone_ (mol_complexSP, mol_complexesN);
	}


else
	{

	HideNoRefresh_ (mol_complexSP, mol_complexesN);


	ShowBackbone_ (mol_complexSP, mol_complexesN);
	}


(*refreshIP)++;
MainRefresh_ (mol_complexSP, mol_complexesN, runtimeSP, configSP, guiSP,
	      nearest_atomSP, pixelsN, *refreshIP);


ControlRefresh_ (mol_complexSP + runtimeSP->default_complexI, configSP, guiSP);


return COMMAND_BACKBONE;
}
