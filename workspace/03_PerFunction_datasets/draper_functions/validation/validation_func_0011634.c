stun_attr_is_addr(stun_attr_ref attr) {

  if(attr) {
    switch(stun_attr_get_type(attr)) {
    case STUN_ATTRIBUTE_XOR_MAPPED_ADDRESS:
    case STUN_ATTRIBUTE_XOR_PEER_ADDRESS:
    case STUN_ATTRIBUTE_XOR_RELAYED_ADDRESS:
    case STUN_ATTRIBUTE_MAPPED_ADDRESS:
    case STUN_ATTRIBUTE_ALTERNATE_SERVER:
    case OLD_STUN_ATTRIBUTE_RESPONSE_ADDRESS:
    case OLD_STUN_ATTRIBUTE_SOURCE_ADDRESS:
    case OLD_STUN_ATTRIBUTE_CHANGED_ADDRESS:
    case OLD_STUN_ATTRIBUTE_REFLECTED_FROM:
    case STUN_ATTRIBUTE_RESPONSE_ORIGIN:
    case STUN_ATTRIBUTE_OTHER_ADDRESS:
      return 1;
      break;
    default:
      ;
    };
  }
  return 0;
}
