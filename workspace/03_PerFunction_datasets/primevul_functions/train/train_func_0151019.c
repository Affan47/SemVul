HeaderUtility::requestHeadersValid(const RequestHeaderMap& headers) {

  if (headers.Host() && !HeaderUtility::authorityIsValid(headers.Host()->value().getStringView())) {
    return SharedResponseCodeDetails::get().InvalidAuthority;
  }
  return absl::nullopt;
}
