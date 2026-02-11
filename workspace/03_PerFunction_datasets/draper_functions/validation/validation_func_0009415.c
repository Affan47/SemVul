smartctl_get_drives(const std::string& dev, const std::string& type,
	  int from, int to, std::vector<StorageDeviceRefPtr>& drives, ExecutorFactoryRefPtr ex_factory)
{
	hz::intrusive_ptr<CmdexSync> smartctl_ex = ex_factory->create_executor(ExecutorFactory::ExecutorSmartctl);

	for (int i = from; i <= to; ++i) {
		std::string type_arg = hz::string_sprintf(type.c_str(), i);
		StorageDeviceRefPtr drive(new StorageDevice(dev, type_arg));


		std::string error_msg = drive->fetch_basic_data_and_parse(smartctl_ex);
		std::string output = drive->get_info_output();


		if (app_pcre_match("/VALID ARGUMENTS ARE/mi", output)) {
			break;
		}

		if (!error_msg.empty()) {
			debug_out_info("app", "Smartctl returned with an error: " << error_msg << "\n");
		} else {
			drives.push_back(drive);
		}
	}

	return std::string();
}
