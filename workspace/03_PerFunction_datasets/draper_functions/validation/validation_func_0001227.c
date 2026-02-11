Function_(const vector<string>& args,bool flag_str)
{
	if(!AssertArgument(args, 3)) return ("");

	string word = args[2];
	for(unsigned int i=3;i<args.size();i++) word+=string(" ")+args[i];
#if 0
	string entryname;
	int st,end;
	TKawariEngine::DecodeEntryName(args[1],entryname,st,end);

	TEntry entry=Engine->CreateEntry(entryname);

	TWordID id;
	if(flag) id=Engine->CreateStrWord(word);
	 else id=Engine->CreateWord(word);

	entry.Insert(0,id);
#else
	TEntryRange range=Engine->GetEntryRange(args[1]);
	TWordID wid=(flag_str)?
		Engine->CreateStrWord(word):Engine->CreateWord(word);
	range.Entry.Insert(0,wid);
#endif
	return("");
}
