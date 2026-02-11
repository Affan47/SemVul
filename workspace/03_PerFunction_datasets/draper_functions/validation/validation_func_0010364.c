removeDefinition(Symbol findkey)
{
	int	index;
	void	*d;
	DictionaryEntry *de;


	if (!(de = this->getDictionaryEntry(findkey)))
		return NUL(void*);

	d =  de->definition;

	index = this->List::getPosition(de);
	ASSERT(index);

	if (!this->deleteElement(index))
		return NUL(void*);

	delete de;

	return d;
}
