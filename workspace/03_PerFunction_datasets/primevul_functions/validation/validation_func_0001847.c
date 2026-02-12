static bool ethereum_signing_check(EthereumSignTx *msg) {
  if (!msg->has_gas_price || !msg->has_gas_limit) {
    return false;
  }

  if (msg->to.size != 20 && msg->to.size != 0) {

    return false;
  }


  if (msg->to.size == 0 && (!msg->has_data_length || msg->data_length == 0)) {
    return false;
  }

  if (msg->gas_price.size + msg->gas_limit.size > 30) {

    return false;
  }

  return true;
}
