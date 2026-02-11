visit(const char* value,orbOptions::Source) throw (orbOptions::BadParam) {

    if (!isValidId(value)) {
      throw orbOptions::BadParam(key(),value,"id is not "ORB_ID_STRING);
    }
    if( strcmp(value, myOrbId()) ) {
      if( omniORB::trace(1) ) {
	omniORB::logger l;
	l << "WARNING -- using ORBid " << value
	  << " (should be " << ORB_ID_STRING << ")." << "\n";
      }
    }
  }
