absl::string_view ExtractorImpl::extractJWT(absl::string_view value_str,
                                            absl::string_view::size_type after) const {
  const auto starting = value_str.find_first_of(ConstantBase64UrlEncodingCharsPlusDot, after);
  if (starting == value_str.npos) {
    return value_str;
  }

  auto ending = value_str.find_first_not_of(ConstantBase64UrlEncodingCharsPlusDot, starting);
  if (ending == value_str.npos) {
    return value_str.substr(starting);
  }
  return value_str.substr(starting, ending - starting);
}
