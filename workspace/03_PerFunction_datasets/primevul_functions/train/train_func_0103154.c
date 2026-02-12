bool ZipStreamBuf::crcValid() const
{
	if (!_ptrBuf) return true;
	return _crc32.checksum() == _expectedCrc32;
}
