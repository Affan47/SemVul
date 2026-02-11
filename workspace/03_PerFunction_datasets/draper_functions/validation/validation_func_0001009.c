genericMessageSize(string uid,
				    size_t messageNumber,
				    callback::message &callback)
{
	if (!fixGenericMessageNumber(uid, messageNumber))
	{
		callback.fail("Invalid message number.");
		return;
	}

	callback.messageSizeCallback(messageNumber, 0);

	callback.success("OK");
}
