void initialize(const string &path, bool owner) {
		TRACE_POINT();
		this->path  = path;
		this->owner = owner;


		makeDirTree(path, "u=rwx,g=rx,o=rx");
	}
