writeToDevice(char c)
{
	poco_assert_dbg (_pOstr);

	if (c == '\r' || (c == '\n' && _lastChar != '\r'))
		_pOstr->write(_newLine.data(), (std::streamsize) _newLine.length());
	if (c != '\n' && c != '\r')
		_pOstr->put(c);
	_lastChar = c;
	return charToInt(c);
}
