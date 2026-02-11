load(ifstream & fp){
		NPR_FMN *npr = new NPR_FMN();
		size_t type = loadValue<size_t>(fp);
		if(type!=FMN_NPR) {
			abort();
		}
		npr->nsv = NSV::load(fp);
		npr->psv = PSV::load(fp);
		npr->rmq = RMQ_succinct_lcp::load(fp);
		return npr;
	}
