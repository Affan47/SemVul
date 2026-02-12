std::istream *istream_file(const std::string &fname, bool treat_failure_as_error)
{
	LOG_FS << "Streaming " << fname << " for reading.\n";
	if (fname.empty()) {
		ERR_FS << "Trying to open file with empty name.\n";
		bfs::ifstream *s = new bfs::ifstream();
		s->clear(std::ios_base::failbit);
		return s;
	}


	try
	{
		boost::iostreams::file_descriptor_source fd(iostream_path(fname), std::ios_base::binary);

		if (!fd.is_open() && treat_failure_as_error) {
			ERR_FS << "Could not open '" << fname << "' for reading.\n";
		}
		return new boost::iostreams::stream<boost::iostreams::file_descriptor_source>(fd, 4096, 0);
	}
	catch(const std::exception ex)
	{
		if(treat_failure_as_error)
		{
			ERR_FS << "Could not open '" << fname << "' for reading.\n";
		}
		bfs::ifstream *s = new bfs::ifstream();
		s->clear(std::ios_base::failbit);
		return s;
	}
}
