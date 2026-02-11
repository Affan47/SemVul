takeArray(QByteArray *from, int size, bool del)
{
	QByteArray a;
	if(size == 0) {
		a = *from;
		if(del)
			from->resize(0);
	}
	else {
		if(size > (int)from->size())
			size = from->size();
		a.resize(size);
		char *r = from->data();
		memcpy(a.data(), r, size);
		if(del) {
			int newsize = from->size()-size;
			memmove(r, r+size, newsize);
			from->resize(newsize);
		}
	}
	return a;
}
