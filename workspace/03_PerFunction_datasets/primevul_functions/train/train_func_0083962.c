inline bool loadModule(const char* filename, IR::Module& outModule)
{

	std::vector<U8> fileBytes;
	if(!loadFile(filename, fileBytes)) { return false; }


	if(*(U32*)fileBytes.data() == 0x6d736100)
	{ return loadBinaryModule(fileBytes.data(), fileBytes.size(), outModule); }
	else
	{

		fileBytes.push_back(0);


		std::vector<WAST::Error> parseErrors;
		if(!WAST::parseModule(
			   (const char*)fileBytes.data(), fileBytes.size(), outModule, parseErrors))
		{
			Log::printf(Log::error, "Error parsing WebAssembly text file:\n");
			reportParseErrors(filename, parseErrors);
			return false;
		}

		return true;
	}
}
