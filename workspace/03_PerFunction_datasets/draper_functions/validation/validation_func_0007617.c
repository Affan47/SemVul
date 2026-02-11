strToGV(const std::string& s) {
	return s=="Open"?GV_OPEN:s=="Closed"?GV_CLOSED:GV_OTHER;
}
