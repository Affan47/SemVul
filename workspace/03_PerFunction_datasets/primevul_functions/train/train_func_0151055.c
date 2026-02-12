Config::Config(const envoy::extensions::filters::http::header_to_metadata::v3::Config config,
               const bool per_route) {
  request_set_ = Config::configToVector(config.request_rules(), request_rules_);
  response_set_ = Config::configToVector(config.response_rules(), response_rules_);


  if (per_route && !response_set_ && !request_set_) {
    throw EnvoyException("header_to_metadata_filter: Per filter configs must at least specify "
                         "either request or response rules");
  }
}
