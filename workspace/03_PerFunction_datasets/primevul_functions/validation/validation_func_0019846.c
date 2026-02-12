bool RGWSwiftWebsiteHandler::can_be_website_req() const
{

  static const std::set<boost::string_ref> ws_methods = { "GET", "HEAD" };
  if (ws_methods.count(s->info.method) == 0) {
    return false;
  }


  if (! s->auth.identity) {
    return true;
  }


  if (s->auth.identity->is_anonymous() || is_web_mode()) {
    return true;
  }

  return false;
}
