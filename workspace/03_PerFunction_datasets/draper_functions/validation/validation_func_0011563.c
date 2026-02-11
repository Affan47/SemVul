add_type1_encoding(Type1Encoding *e)
{
    if (_encoding) {
	for (Type1Item** t1i = _items.begin(); t1i < _items.end(); t1i++)
	    if (*t1i == _encoding) {
		delete _encoding;
		*t1i = _encoding = e;
		return;
	    }
    }
    _encoding = e;
    add_item(e);
}
