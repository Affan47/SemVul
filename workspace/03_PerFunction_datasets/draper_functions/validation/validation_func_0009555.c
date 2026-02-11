DrawNiceBonds_ (MolComplexS *mol_complexSP, int mol_complexesN,
		       ConfigS *configSP, GUIS *guiSP,
		       NearestAtomS *nearest_atomSP, size_t pixelsN,
		       unsigned int refreshI)
{
static size_t		pixelI;
static size_t		bonds_drawnN = 0;
static int		imageI, imagesN;
static int		mol_complexI;
static MolComplexS	*curr_mol_complexSP, *partner_mol_complexSP;
static size_t		atomsN, atomI;
static AtomS		*curr_atomSP, *partner_atomSP;
static int		bondsN, bondI;
static TrueBondS	*curr_bondSP;
static Aux2S		aux2S;


if (mol_complexesN == 0) return 0;


for (pixelI = 0; pixelI < pixelsN; pixelI++)
	{
	(nearest_atomSP + pixelI)->auxiliaryI = 0;
	}


if (configSP->stereoF) imagesN = 2;
else imagesN = 1;


aux2S.configSP = configSP;
aux2S.guiSP = guiSP;
aux2S.nearest_atomSP = nearest_atomSP;
aux2S.pixelsN = pixelsN;
aux2S.refreshI = refreshI;


for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
    {

    curr_mol_complexSP = mol_complexSP + mol_complexI;


    atomsN = curr_mol_complexSP->atomsN;
    if (atomsN == 0) continue;


    aux2S.mol_complexI = mol_complexI;


    aux2S.bond_probe_radius = curr_mol_complexSP->bond_probe_radius;


    for (atomI = 0; atomI < atomsN; atomI++)
	{

	curr_atomSP = curr_mol_complexSP->atomSP + atomI;


	if (curr_atomSP->hiddenF) continue;


	if (!curr_atomSP->inside_slabF) continue;


	if (!curr_atomSP->inside_windowF) continue;


	aux2S.atom1SP = curr_atomSP;


	aux2S.atomI = atomI;


	bondsN = curr_atomSP->bondsN;


	for (bondI = 0; bondI < bondsN; bondI++)
	    {

	    curr_bondSP = curr_atomSP->true_bondSA + bondI;


	    if (curr_bondSP->bond_styleI != NICE_BONDS) continue;


	    if (curr_bondSP->bond_typeI == 0) continue;


	    partner_mol_complexSP = mol_complexSP +
				    curr_bondSP->neighbor_mol_complexI;


	    partner_atomSP = partner_mol_complexSP->atomSP +
			     curr_bondSP->neighbor_arrayI;


	    if (partner_atomSP->hiddenF) continue;


	    if (!partner_atomSP->inside_slabF) continue;


	    if (!partner_atomSP->inside_windowF) continue;


	    aux2S.bondI = bondI;


	    aux2S.curr_bondSP = curr_bondSP;


	    aux2S.atom2SP = partner_atomSP;


	    for (imageI = 0; imageI < imagesN; imageI++)
		{

		aux2S.imageI = imageI;


		HalfNiceBond_ (&aux2S, bondI);


		bonds_drawnN++;
		}
	    }
	}
    }


return bonds_drawnN;
}
