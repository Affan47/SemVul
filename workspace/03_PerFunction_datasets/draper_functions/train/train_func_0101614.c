Handle(Arc::Message* msg) const {
  pdp_container_t::const_iterator it;
  bool r = false;
  for(it=pdps_.begin();it!=pdps_.end();it++){
    r = it->pdp->isPermitted(msg);
    if((r == true) && (it->action == PDPDesc::breakOnAllow)) break;
    if((r == false) && (it->action == PDPDesc::breakOnDeny)) break;
    if(it->action == PDPDesc::breakAlways) break;
  }
  return r;
}

}
