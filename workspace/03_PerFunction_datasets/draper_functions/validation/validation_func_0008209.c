Function(const vector<string>& args)
{
	if(!AssertArgument(args, 1, 1)) return ("");

#if 0
	return IntToString(Engine->EntryCollectionSize());
#else
	int entryno=0;
	TEntry rootentry=Engine->CreateEntry(".");
	vector<TEntry> entrycol;
	if(rootentry.FindTree(entrycol)){

		sort(entrycol.begin(), entrycol.end());
		vector<TEntry>::iterator end=unique(entrycol.begin(), entrycol.end());
		for(vector<TEntry>::iterator it=entrycol.begin(); it!=end; it++){
			if (it->GetName().size()) entryno++;
		}
	}
	return IntToString(entryno);
#endif
}
