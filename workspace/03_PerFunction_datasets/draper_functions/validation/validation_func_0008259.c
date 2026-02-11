setStaticReference(int classID, int fieldOffset, int objectID) {
	if (classReferences.size() <= (unsigned int) classID)
		classReferences.resize(classID + 1);

	if (objectID)
		classReferences[classID][fieldOffset] = getByID(objectID);
	else
		classReferences[classID][fieldOffset] = NULL;
}
