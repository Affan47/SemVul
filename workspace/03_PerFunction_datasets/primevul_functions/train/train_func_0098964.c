GenerationPtr getGeneration(unsigned int number) const {


		return ptr(new Generation(path, number));
	}
