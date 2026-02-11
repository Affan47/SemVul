APar_MetaData_atom_Init(const char* atom_path, const char* MD_Payload, const uint32_t atomFlags) {

	if (metadata_style != ITUNES_STYLE) return NULL;
	bool retain_atom = true;

	if ( strlen(MD_Payload) == 0 ) {
		retain_atom = false;
	}

	if (retain_atom) {
		APar_Verify__udta_meta_hdlr__atom();
	}

	AtomicInfo* desiredAtom = APar_FindAtom(atom_path, retain_atom, VERSIONED_ATOM, 0);
	if (desiredAtom == NULL) return NULL;
	modified_atoms = true;

	if (! retain_atom) {
		AtomicInfo* parent_atom = &parsedAtoms[ APar_FindParentAtom(desiredAtom->AtomicNumber, desiredAtom->AtomicLevel) ];
		if (desiredAtom->AtomicNumber > 0 && parent_atom->AtomicNumber > 0) {
			APar_EliminateAtom(parent_atom->AtomicNumber, desiredAtom->NextAtomNumber);
			APar_FlagMovieHeader();
			return NULL;
		}

	} else {
		parsedAtoms[desiredAtom->AtomicNumber].AtomicData = (char*)malloc(sizeof(char)* MAXDATA_PAYLOAD + 1 );
		memset(parsedAtoms[desiredAtom->AtomicNumber].AtomicData, 0, sizeof(char)* MAXDATA_PAYLOAD + 1 );

		parsedAtoms[desiredAtom->AtomicNumber].AtomicLength = 16;
		parsedAtoms[desiredAtom->AtomicNumber].AtomicVerFlags = atomFlags;
		parsedAtoms[desiredAtom->AtomicNumber].AtomicContainerState = CHILD_ATOM;
		parsedAtoms[desiredAtom->AtomicNumber].AtomicClassification = VERSIONED_ATOM;
		APar_FlagMovieHeader();
	}
	return desiredAtom;
}
