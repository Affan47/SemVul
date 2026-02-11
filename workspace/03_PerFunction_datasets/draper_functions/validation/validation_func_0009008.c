readString(io::IReadFile* file, ChunkData& data, core::stringc& out)
{
	c8 c = 0;
	out = "";

	while (c!='\n')
	{
		file->read(&c, sizeof(c8));
		if (c!='\n')
			out.append(c);

	}
	data.read+=out.size()+1;
}
