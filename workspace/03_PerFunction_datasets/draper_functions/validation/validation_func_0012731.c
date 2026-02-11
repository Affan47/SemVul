dsm_malloc(string blockId, int size) throw (DsmException) {
		ostringstream outs;
		outs << "dsm_malloc " << this->nid << " " << blockId << " " << size;
		this->send(outs.str());
		string response = this->receive();
		if (response.find("ERROR") == 0) {
			throw DsmException(response);
		} else {
			istringstream ins;
			ins.str(response);
			unsigned long addr;
			ins >> addr;
		}
	}
