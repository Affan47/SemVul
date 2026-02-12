TEST_METHOD(13) {


		ServerInstanceDir dir(parentDir + "/passenger-test.1234");
		ServerInstanceDir::GenerationPtr generation = dir.newGeneration(true, "nobody", nobodyGroup, 0, 0);
		string path = generation->getPath();
		generation->detach();
		generation.reset();
		ensure_equals(getFileType(path), FT_DIRECTORY);
	}
