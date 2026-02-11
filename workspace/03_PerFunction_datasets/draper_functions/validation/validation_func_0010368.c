collectIncludeFile(set<string>& S)
{
	list<Klass* >::iterator 	k;

	for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->collectIncludeFile(S);
	merge(S, fIncludeFileSet);
}
