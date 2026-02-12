int RGWSwiftWebsiteHandler::retarget_bucket(RGWOp* op, RGWOp** new_op)
{
  ldout(s->cct, 10) << "Starting retarget" << dendl;
  RGWOp* op_override = nullptr;


  if (can_be_website_req()) {
    const auto& ws_conf = s->bucket_info.website_conf;
    const auto& index = s->bucket_info.website_conf.get_index_doc();

    if (s->decoded_uri.back() != '/') {
      op_override = get_ws_redirect_op();
    } else if (! index.empty() && is_index_present(index)) {
      op_override = get_ws_index_op();
    } else if (ws_conf.listing_enabled) {
      op_override = get_ws_listing_op();
    }
  }

  if (op_override) {
    handler->put_op(op);
    op_override->init(store, s, handler);

    *new_op = op_override;
  } else {
    *new_op = op;
  }


  return ! op_override && is_web_mode() ? -ENOENT : 0;
}
