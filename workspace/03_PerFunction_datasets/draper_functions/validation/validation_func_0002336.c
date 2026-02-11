Hide_ (MolComplexS *mol_complexSP, int mol_complexesN,
	   RuntimeS *runtimeSP,
	   ConfigS *configSP, GUIS *guiSP,
	   NearestAtomS *nearest_atomSP, size_t pixelsN,
	   unsigned int *refreshIP)
{
int		mol_complexI;
MolComplexS	*curr_mol_complexSP;
size_t		atomsN, atomI;
AtomS		*curr_atomSP;


for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
	{

	curr_mol_complexSP = mol_complexSP + mol_complexI;


	if (curr_mol_complexSP->catchF == 0) continue;


	atomsN = curr_mol_complexSP->atomsN;
	if (atomsN == 0) continue;


	for (atomI = 0; atomI < atomsN; atomI++)
		{

		curr_atomSP = curr_mol_complexSP->atomSP + atomI;


		if (curr_atomSP->selectedF) curr_atomSP->hiddenF = 1;
		}
	}


HideBackbone_ (mol_complexSP, mol_complexesN);


(*refreshIP)++;
MainRefresh_ (mol_complexSP, mol_complexesN, runtimeSP, configSP, guiSP,
	      nearest_atomSP, pixelsN, *refreshIP);


ControlRefresh_ (mol_complexSP + runtimeSP->default_complexI, configSP, guiSP);


return COMMAND_HIDE;
}
