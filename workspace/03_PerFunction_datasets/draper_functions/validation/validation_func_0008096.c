sendFile(const std::string& path, const std::string& mediaType)
{
	poco_assert (!_pStream);

	File f(path);
	Timestamp dateTime    = f.getLastModified();
	File::FileSize length = f.getSize();
	set("Last-Modified", DateTimeFormatter::format(dateTime, DateTimeFormat::HTTP_FORMAT));
	setContentLength(static_cast<int>(length));
	setContentType(mediaType);
	setChunkedTransferEncoding(false);

	Poco::FileInputStream istr(path);
	if (istr.good())
	{
		_pStream = new HTTPHeaderOutputStream(_session);
		write(*_pStream);
		StreamCopier::copyStream(istr, *_pStream);
	}
	else throw OpenFileException(path);
}
