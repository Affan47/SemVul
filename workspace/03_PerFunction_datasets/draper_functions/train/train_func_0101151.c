SetIP(uint32 ip_as_host_order_integer) {
  hostname_.clear();
  literal_ = false;
  ip_ = IPAddress(ip_as_host_order_integer);
}
