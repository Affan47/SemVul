AreReadyForWriting()
{
	Iterator out;
	for ( out=mOutPorts.begin(); out!=mOutPorts.end(); out++)
		if (!(*out)->CanProduce()) return false;

	return true;
}
