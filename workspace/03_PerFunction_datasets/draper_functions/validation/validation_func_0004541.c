cbegin() const {
	checkType(OBJECT);
	if(_type == BSON::UNDEFINED)throw std::runtime_error{"wrong type"};
	return _objectValue.cbegin();
}
