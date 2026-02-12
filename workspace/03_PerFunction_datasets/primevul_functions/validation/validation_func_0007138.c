int RGWHandler_REST_S3Website::serve_errordoc(int http_ret, const string& errordoc_key) {
  int ret = 0;
  s->formatter->reset();

  std::shared_ptr<RGWGetObj_ObjStore_S3Website> getop( static_cast<RGWGetObj_ObjStore_S3Website*>(op_get()));
  if (getop.get() == NULL) {
    return -1;
  }
  getop->init(store, s, this);
  getop->range_str = NULL;
  getop->if_mod = NULL;
  getop->if_unmod = NULL;
  getop->if_match = NULL;
  getop->if_nomatch = NULL;
  s->object = errordoc_key;

  ret = init_permissions(getop.get());
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, init_permissions ret=" << ret << dendl;
    return -1;
  }

  ret = read_permissions(getop.get());
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, read_permissions ret=" << ret << dendl;
    return -1;
  }

  if (http_ret) {
     getop->set_custom_http_response(http_ret);
  }

  ret = getop->init_processing();
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, init_processing ret=" << ret << dendl;
    return -1;
  }

  ret = getop->verify_op_mask();
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, verify_op_mask ret=" << ret << dendl;
    return -1;
  }

  ret = getop->verify_permission();
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, verify_permission ret=" << ret << dendl;
    return -1;
  }

  ret = getop->verify_params();
  if (ret < 0) {
    ldout(s->cct, 20) << "serve_errordoc failed, verify_params ret=" << ret << dendl;
    return -1;
  }


  getop->pre_exec();


  getop->execute();
  getop->complete();
  return 0;

}
