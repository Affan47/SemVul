Function(const vector<string>& args)
{
	TKawariLogger &Logger=GetLogger();
	if(args.size()>=2) {
		Logger.GetStream() << args[1];
		for(unsigned int i=2;i<args.size();i++) Logger.GetStream() << " " << args[i];
	}

	Logger.GetStream() << endl;

	return("");
}
