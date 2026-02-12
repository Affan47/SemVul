void ethereumFormatAmount(const bignum256 *amnt, const TokenType *token,
                          uint32_t cid, char *buf, int buflen) {
  bignum256 bn1e9;
  bn_read_uint32(1000000000, &bn1e9);
  const char *suffix = NULL;
  int decimals = 18;
  if (token == UnknownToken) {
    strlcpy(buf, "Unknown token value", buflen);
    return;
  } else if (token != NULL) {
    suffix = token->ticker;
    decimals = token->decimals;
  } else if (bn_is_less(amnt, &bn1e9)) {
    suffix = " Wei";
    decimals = 0;
  } else {
    if (tx_type == 1 || tx_type == 6) {
      suffix = " WAN";
    } else {

      switch (cid) {
        case 1:
          suffix = " ETH";
          break;
        case 2:
          suffix = " EXP";
          break;
        case 3:
          suffix = " tROP";
          break;
        case 4:
          suffix = " tRIN";
          break;
        case 8:
          suffix = " UBQ";
          break;
        case 20:
          suffix = " EOSC";
          break;
        case 28:
          suffix = " ETSC";
          break;
        case 30:
          suffix = " RBTC";
          break;
        case 31:
          suffix = " tRBTC";
          break;
        case 42:
          suffix = " tKOV";
          break;
        case 61:
          suffix = " ETC";
          break;
        case 62:
          suffix = " tETC";
          break;
        case 64:
          suffix = " ELLA";
          break;
        case 820:
          suffix = " CLO";
          break;
        case 1987:
          suffix = " EGEM";
          break;
        default:
          suffix = " UNKN";
          break;
      }
    }
  }
  bn_format(amnt, NULL, suffix, decimals, 0, false, buf, buflen);
}
