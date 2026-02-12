static bool update_mtime(unsigned ivalid, bool trust_local_mtime)
{

	if (ivalid & ATTR_MTIME_SET)
		return true;


	if (trust_local_mtime)
		return true;


	if ((ivalid & ATTR_SIZE) && (ivalid & (ATTR_OPEN | ATTR_FILE)))
		return false;


	return true;
}
