addOption(std::auto_ptr<Option> option) {
	SharedOptPtr opt(option.release());
	options_.push_back(opt);
}
