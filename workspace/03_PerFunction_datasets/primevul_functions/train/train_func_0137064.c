TEST_METHOD(3) {


		{
			ServerInstanceDir dir(parentDir + "/passenger-test.1234");
		}
		ensure_equals(listDir(parentDir).size(), 0u);

		{
			ServerInstanceDir dir(parentDir + "/passenger-test.1234");
			createGenerationDir(dir.getPath(), 1);
		}
		ensure_equals(listDir(parentDir).size(), 1u);
	}
