parse_opt (int key, char *arg, struct argp_state *state)
{
  char *endptr;
  static unsigned char pattern[16];
  double v;

  switch (key)
    {
    case 'c':
      count = ping_cvt_number (arg, 0, 1);
      break;

    case 'd':
      socket_type |= SO_DEBUG;
      break;

    case 'i':
      v = strtod (arg, &endptr);
      if (*endptr)
        argp_error (state, "invalid value (`%s' near `%s')", arg, endptr);
      options |= OPT_INTERVAL;
      interval = v * PING_PRECISION;
      if (!is_root && interval < MIN_USER_INTERVAL)
        error (EXIT_FAILURE, 0, "option value too small: %s", arg);
      break;

    case 'r':
      socket_type |= SO_DONTROUTE;
      break;

    case 's':
      data_length = ping_cvt_number (arg, PING_MAX_DATALEN, 1);
      break;

    case 'n':
      options |= OPT_NUMERIC;
      break;

    case 'p':
      decode_pattern (arg, &pattern_len, pattern);
      patptr = pattern;
      break;

    case 'q':
      options |= OPT_QUIET;
      break;

    case 'T':
      tos = ping_cvt_number (arg, 255, 1);
      break;

    case 'w':
      timeout = ping_cvt_number (arg, INT_MAX, 0);
      break;

    case 'R':
      options |= OPT_RROUTE;
      break;

    case 'W':
      linger = ping_cvt_number (arg, INT_MAX, 0);
      break;

    case 'v':
      options |= OPT_VERBOSE;
      break;

    case 'l':
      preload = strtoul (arg, &endptr, 0);
      if (*endptr || preload > INT_MAX)
        error (EXIT_FAILURE, 0, "invalid preload value (%s)", arg);
      break;

    case 'f':
      options |= OPT_FLOOD;
      break;

    case 't':
      ping_type = decode_type (arg);
      break;

    case ARG_ECHO:
      ping_type = decode_type ("echo");
      break;

    case ARG_TIMESTAMP:
      ping_type = decode_type ("timestamp");
      break;

    case ARG_ADDRESS:
      ping_type = decode_type ("address");
      break;

    case ARG_ROUTERDISCOVERY:
      ping_type = decode_type ("router");
      break;

    case ARG_TTL:
      ttl = ping_cvt_number (arg, 255, 0);
      break;

    case ARG_IPTIMESTAMP:
      options |= OPT_IPTIMESTAMP;
      suboptions |= decode_ip_timestamp (arg);
      break;

    case ARGP_KEY_NO_ARGS:
      argp_error (state, "missing host operand");

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
