HeaderUtility::getAllOfHeaderAsString(const HeaderMap& headers, const Http::LowerCaseString& key) {
  GetAllOfHeaderAsStringResult result;
  const auto header_value = headers.getAll(key);

  if (header_value.empty()) {


  } else if (header_value.size() == 1 ||
             !Runtime::runtimeFeatureEnabled(
                 "envoy.reloadable_features.http_match_on_all_headers")) {
    result.result_ = header_value[0]->value().getStringView();
  } else {


    absl::InlinedVector<absl::string_view, 3> string_view_vector;
    string_view_vector.reserve(header_value.size());
    for (size_t i = 0; i < header_value.size(); i++) {
      string_view_vector.push_back(header_value[i]->value().getStringView());
    }
    result.result_backing_string_ = absl::StrJoin(string_view_vector, ",");
  }

  return result;
}
