TEST_METHOD(7) {


		ServerInstanceDir dir(parentDir + "/passenger-test.1234");
		ServerInstanceDir::GenerationPtr generation = dir.newGeneration(true,
			"nobody", nobodyGroup, 0, 0);
		string path = generation->getPath();
		generation.reset();
		ensure_equals(getFileType(path), FT_NONEXISTANT);
	}
