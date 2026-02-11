skipSection(io::IXMLReader* reader, bool reportSkipping)
{
#ifdef _DEBUG
	os::Printer::log("irrMesh skipping section", core::stringc(reader->getNodeName()).c_str());
#endif


	if (reader->isEmptyElement())
		return;


	u32 tagCounter = 1;

	while(tagCounter && reader->read())
	{
		if (reader->getNodeType() == io::EXN_ELEMENT &&
			!reader->isEmptyElement())
		{
			#ifdef _DEBUG
			if (reportSkipping)
				os::Printer::log("irrMesh unknown element:", core::stringc(reader->getNodeName()).c_str());
			#endif

			++tagCounter;
		}
		else
		if (reader->getNodeType() == io::EXN_ELEMENT_END)
			--tagCounter;
	}
}
