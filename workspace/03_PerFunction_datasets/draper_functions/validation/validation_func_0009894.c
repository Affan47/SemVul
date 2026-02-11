getParentFolder(callback::folderList &callback1,
					 callback &callback2) const
{
	if (isDestroyed(callback2))
		return;

	string ppath("");

	size_t n=path.rfind('.');

	if (n != std::string::npos)
		ppath=path.substr(0, n);

	myserver->findFolder(ppath, callback1, callback2);
}
