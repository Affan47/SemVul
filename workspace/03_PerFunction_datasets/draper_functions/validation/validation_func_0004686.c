deviceSendSetRequest(std::string deviceAndAddress, Value& newValue)
{
	std::string deviceName;
	Address address;

	parseDeviceAndAddress(deviceAndAddress, deviceName, address);
	std::cout << "DeviceManager::deviceSendSetRequest deviceName = " << deviceName << " address = " << address << std::endl;


	deviceSendSetRequest(deviceName, address, newValue);
}
