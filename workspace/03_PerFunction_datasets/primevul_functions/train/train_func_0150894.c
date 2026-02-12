void HeaderUtility::stripPortFromHost(RequestHeaderMap& headers, uint32_t listener_port) {

  if (headers.getMethodValue() == Http::Headers::get().MethodValues.Connect) {


    return;
  }
  const absl::string_view original_host = headers.getHostValue();
  const absl::string_view::size_type port_start = original_host.rfind(':');
  if (port_start == absl::string_view::npos) {
    return;
  }

  const auto v6_end_index = original_host.rfind("]");
  if (v6_end_index == absl::string_view::npos || v6_end_index < port_start) {
    if ((port_start + 1) > original_host.size()) {
      return;
    }
    const absl::string_view port_str = original_host.substr(port_start + 1);
    uint32_t port = 0;
    if (!absl::SimpleAtoi(port_str, &port)) {
      return;
    }
    if (port != listener_port) {

      return;
    }
    const absl::string_view host = original_host.substr(0, port_start);
    headers.setHost(host);
  }
}
