rgw::auth::s3::LDAPEngine::authenticate(
  const DoutPrefixProvider* dpp,
  const boost::string_view& access_key_id,
  const boost::string_view& signature,
  const boost::string_view& session_token,
  const string_to_sign_t& string_to_sign,
  const signature_factory_t&,
  const completer_factory_t& completer_factory,
  const req_state* const s) const
{

  rgw::RGWToken base64_token;
  try {
    base64_token = rgw::from_base64(access_key_id);
  } catch (...) {
    base64_token = std::string("");
  }

  if (! base64_token.valid()) {
    return result_t::deny();
  }


  if (ldh->auth(base64_token.id, base64_token.key) != 0) {
    return result_t::deny(-ERR_INVALID_ACCESS_KEY);
  }

  auto apl = apl_factory->create_apl_remote(cct, s, get_acl_strategy(),
                                            get_creds_info(base64_token));
  return result_t::grant(std::move(apl), completer_factory(boost::none));
}
