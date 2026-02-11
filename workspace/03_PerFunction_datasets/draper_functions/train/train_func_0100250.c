getParentFolder(const mail::folder *folder,
				    mail::ACCOUNT::FolderList &list)
{
	if (disconnected())
		return false;

	mail::ACCOUNT::readFoldersCallback callback1(list);
	mail::ACCOUNT::callback callback2 (*this);

	folder->getParentFolder(callback1, callback2);

	return eventloop(callback2);
}
