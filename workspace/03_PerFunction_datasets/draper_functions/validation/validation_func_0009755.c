rotateAroundZaxes(MolSymMolecule* mol, gint n)
{
	gint i;
	gdouble s,c;
	MolSymAtom *atomList,*tmpAtomList;
	MolSymMolecule tmpMol;
	gdouble eps = 1e-3;

	if(mol->numberOfAtoms >0) eps = mol->listOfAtoms[0].eps;


	tmpMol.numberOfAtoms=mol->numberOfAtoms;
	tmpMol.listOfAtoms = (MolSymAtom*)g_malloc(tmpMol.numberOfAtoms*sizeof(MolSymAtom));
	if (tmpMol.listOfAtoms == NULL)
	 {
		return -1;
	 }


	s = sin(2*PI/n);
	c = cos(2*PI/n);
	if (n<0) s = -s;
	atomList = mol->listOfAtoms;
	tmpAtomList = tmpMol.listOfAtoms;

	for (i=0;i<mol->numberOfAtoms;i++)
	 {
		tmpAtomList->position[0] = c*atomList->position[0] - s*atomList->position[1];
		tmpAtomList->position[1] = s*atomList->position[0] + c*atomList->position[1];

		if ((SQU2(atomList->position[0],atomList->position[1]) > eps*eps) &&
		(SQU2(tmpAtomList->position[0] - atomList->position[0],tmpAtomList->position[1] - atomList->position[1]) <eps*eps))
		{

			g_free(tmpMol.listOfAtoms);
			return 0;
		}

		if (n>0)

			tmpAtomList->position[2] =  atomList->position[2];
		else

			tmpAtomList->position[2] = -atomList->position[2];
		tmpAtomList->type = atomList->type;
		atomList++;;
		tmpAtomList++;
	 }

	atomList = mol->listOfAtoms;
	tmpAtomList = tmpMol.listOfAtoms;

	i = checkequivalence2Molecules(atomList,tmpAtomList,mol->numberOfAtoms);
	g_free(tmpMol.listOfAtoms);
	return i;
}
