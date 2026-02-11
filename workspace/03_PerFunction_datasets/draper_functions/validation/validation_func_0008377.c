fetchCompleted()
{
	try {
		RunLater();
	} catch (...) {

		addMessagePtr->
			fail("An exception occurred while copying messages.  The copy is aborted.");
		addMessagePtr=NULL;
		delete this;
	}
}
