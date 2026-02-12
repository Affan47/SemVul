TEST_METHOD(9) {

		ServerInstanceDir dir(parentDir + "/passenger-test.1234");
		ensure(dir.getNewestGeneration() == NULL);
	}
