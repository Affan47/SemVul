CheckComm(DTR_ptr dtr, std::vector<std::string>& allowed_dirs) {
    if (!dtr->get_delivery_endpoint() || dtr->get_delivery_endpoint() == DTR::LOCAL_DELIVERY)
      return DataDeliveryLocalComm::CheckComm(dtr, allowed_dirs);
    return DataDeliveryRemoteComm::CheckComm(dtr, allowed_dirs);
  }
