dump(orbOptions::sequenceString& result) {

    omniObjAdapter::Options::EndpointURIList::iterator last, i;
    i = omniObjAdapter::options.endpoints.begin();
    last = omniObjAdapter::options.endpoints.end();
    for (; i != last; i++) {
      if ( (*i)->no_publish ) {
	orbOptions::addKVString(key(),(*i)->uri,result);
      }
    }
  }
