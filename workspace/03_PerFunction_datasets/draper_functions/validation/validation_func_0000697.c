LoadApp(std::istream &input)
{
	uint32_t module_size;
	while( (module_size = SeekNextCod(input)) != 0 ) {
		SendStream(input, module_size);
	}
}
