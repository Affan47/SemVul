testVoidIn()
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testVoidIn();
	assert (!result.available());
	activeObj.cont();
	result.wait();
	assert (result.available());
	assert (!result.failed());
	assert (result.data() == 123);
}
