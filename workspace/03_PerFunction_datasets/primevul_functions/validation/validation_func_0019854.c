int RGWSwiftWebsiteHandler::serve_errordoc(const int http_ret,
                                           const std::string error_doc)
{

  s->formatter->reset();

  class RGWGetErrorPage : public RGWGetObj_ObjStore_SWIFT {
  public:
    RGWGetErrorPage(RGWRados* const store,
                    RGWHandler_REST* const handler,
                    req_state* const s,
                    const int http_ret) {


      init(store, s, handler);
      set_get_data(true);
      set_custom_http_response(http_ret);
    }

    int error_handler(const int err_no,
                      std::string* const error_content) override {


      return 0;
    }
  } get_errpage_op(store, handler, s, http_ret);

  s->object = std::to_string(http_ret) + error_doc;

  RGWOp* newop = &get_errpage_op;
  RGWRequest req(0);
  return rgw_process_authenticated(handler, newop, &req, s, true);
}
