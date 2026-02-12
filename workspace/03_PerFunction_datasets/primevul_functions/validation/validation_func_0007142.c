AWSGeneralAbstractor::get_auth_data_v4(const req_state* const s,
                                       const bool using_qs) const
{
  boost::string_view access_key_id;
  boost::string_view signed_hdrs;

  boost::string_view date;
  boost::string_view credential_scope;
  boost::string_view client_signature;

  int ret = rgw::auth::s3::parse_v4_credentials(s->info,
						access_key_id,
						credential_scope,
						signed_hdrs,
						client_signature,
						date,
						using_qs);
  if (ret < 0) {
    throw ret;
  }


  boost::optional<std::string> canonical_headers = \
    get_v4_canonical_headers(s->info, signed_hdrs, using_qs);
  if (canonical_headers) {
    using sanitize = rgw::crypt_sanitize::log_content;
    ldout(s->cct, 10) << "canonical headers format = "
                      << sanitize{*canonical_headers} << dendl;
  } else {
    throw -EPERM;
  }


  auto exp_payload_hash = rgw::auth::s3::get_v4_exp_payload_hash(s->info);


  auto canonical_uri = rgw::auth::s3::get_v4_canonical_uri(s->info);


  auto canonical_qs = rgw::auth::s3::get_v4_canonical_qs(s->info, using_qs);


  auto canonical_req_hash = \
    rgw::auth::s3::get_v4_canon_req_hash(s->cct,
                                         s->info.method,
                                         std::move(canonical_uri),
                                         std::move(canonical_qs),
                                         std::move(*canonical_headers),
                                         signed_hdrs,
                                         exp_payload_hash);

  auto string_to_sign = \
    rgw::auth::s3::get_v4_string_to_sign(s->cct,
                                         AWS4_HMAC_SHA256_STR,
                                         date,
                                         credential_scope,
                                         std::move(canonical_req_hash));

  const auto sig_factory = std::bind(rgw::auth::s3::get_v4_signature,
                                     credential_scope,
                                     std::placeholders::_1,
                                     std::placeholders::_2,
                                     std::placeholders::_3);


  if (is_v4_payload_unsigned(exp_payload_hash) || is_v4_payload_empty(s)) {
    return {
      access_key_id,
      client_signature,
      std::move(string_to_sign),
      sig_factory,
      null_completer_factory
    };
  } else {


    if (!is_v4_payload_streamed(exp_payload_hash)) {
      ldout(s->cct, 10) << "delaying v4 auth" << dendl;


      switch (s->op_type)
      {
        case RGW_OP_CREATE_BUCKET:
        case RGW_OP_PUT_OBJ:
        case RGW_OP_PUT_ACLS:
        case RGW_OP_PUT_CORS:
        case RGW_OP_INIT_MULTIPART:
        case RGW_OP_COMPLETE_MULTIPART:
        case RGW_OP_SET_BUCKET_VERSIONING:
        case RGW_OP_DELETE_MULTI_OBJ:
        case RGW_OP_ADMIN_SET_METADATA:
        case RGW_OP_SET_BUCKET_WEBSITE:
        case RGW_OP_PUT_BUCKET_POLICY:
        case RGW_OP_PUT_OBJ_TAGGING:
        case RGW_OP_PUT_LC:
        case RGW_OP_SET_REQUEST_PAYMENT:
          break;
        default:
          dout(10) << "ERROR: AWS4 completion for this operation NOT IMPLEMENTED" << dendl;
          throw -ERR_NOT_IMPLEMENTED;
      }

      const auto cmpl_factory = std::bind(AWSv4ComplSingle::create,
                                          s,
                                          std::placeholders::_1);
      return {
        access_key_id,
        client_signature,
        std::move(string_to_sign),
        sig_factory,
        cmpl_factory
      };
    } else {


      dout(10) << "body content detected in multiple chunks" << dendl;


      switch(s->op_type)
      {
        case RGW_OP_PUT_OBJ:
          break;
        default:
          dout(10) << "ERROR: AWS4 completion for this operation NOT IMPLEMENTED (streaming mode)" << dendl;
          throw -ERR_NOT_IMPLEMENTED;
      }

      dout(10) << "aws4 seed signature ok... delaying v4 auth" << dendl;


      const auto cmpl_factory = std::bind(AWSv4ComplMulti::create,
                                          s,
                                          date,
                                          credential_scope,
                                          client_signature,
                                          std::placeholders::_1);
      return {
        access_key_id,
        client_signature,
        std::move(string_to_sign),
        sig_factory,
        cmpl_factory
      };
    }
  }
}
