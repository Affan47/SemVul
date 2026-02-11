approx(GLEDrawObject* other) {
	GLEObjectDO* otherc = (GLEObjectDO*)other;
	if (!otherc->getRefPointString()->equals(getRefPointString())) return false;
	GLEArrayImpl* my_args = getProperties()->getArray();
	GLEArrayImpl* other_args = otherc->getProperties()->getArray();
	GLESub* sub = getConstructor()->getSubroutine();
	for (int i = 0; i < sub->getNbParam(); i++) {
		GLEMemoryCell* a1 = my_args->get(i);
		GLEMemoryCell* a2 = other_args->get(i);
		if (!gle_memory_cell_equals(a1, a2)) return false;
	}
	return getPosition().approx(otherc->getPosition());
}
