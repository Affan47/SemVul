TEST_METHOD(6) {


		ServerInstanceDir dir(parentDir + "/passenger-test.1234");
		unsigned int ncontents = listDir(dir.getPath()).size();
		ServerInstanceDir::GenerationPtr generation = dir.newGeneration(true,
			"nobody", nobodyGroup, 0, 0);

		ensure_equals(generation->getNumber(), 0u);
		ensure_equals(getFileType(generation->getPath()), FT_DIRECTORY);
		ensure_equals(listDir(dir.getPath()).size(), ncontents + 1);
	}
