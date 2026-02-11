read(const char* file) {
	matrix_reader<float>* reader = 0;
	std::string file_name = file;
	if (string_has_file_ext(file_name,".fvec")) reader = new fvec_reader(file);
    else if (string_has_file_ext(file_name,".hvec8")) reader = new hvec8_reader(file);
    else if (string_has_file_ext(file_name,".csv") || string_has_file_ext(file_name,".m")) reader = new csv_reader<float>(file);
    else if (string_has_file_ext(file_name,".txt")) reader = new txt_reader<float>(file);
    else if (string_has_file_ext(file_name,".bin16")) reader = new bin_reader(file);
    else if (string_has_file_ext(file_name,".peter8")) reader = new peter8_reader(file);
    else if (string_has_file_ext(file_name,".idx3-ubyte")) reader = new idx3_ubyte_reader(file);

	if(!reader) {
		cout << "Can't open " << file << "\n";
		throw "No reader for this file format";
	}

	height = reader->get_height();
	width = reader->get_width();

	if(bShared) {
		size_t* _data = (size_t*)create_shared_mem(key, width*height*sizeof(double) + 2*sizeof(size_t), &_shmid);
		*_data++ = width;
		*_data++ = height;
		data = (double*)_data;
	} else {
		data = new double[width*height];
	}

	fflush(stdout);

	float* tmpdata = new float[width*height];
    reader->read(tmpdata);
    for(int i=0; i<width*height; i++) data[i] = tmpdata[i];
    delete tmpdata;

	delete reader;

	return true;
}
