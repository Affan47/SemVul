read_trace_flags(char *arg)
{
    char *c;
    rtsBool enabled = rtsTrue;


    RtsFlags.TraceFlags.scheduler      = rtsTrue;
    RtsFlags.TraceFlags.gc             = rtsTrue;
    RtsFlags.TraceFlags.sparks_sampled = rtsTrue;
    RtsFlags.TraceFlags.user           = rtsTrue;

    for (c  = arg; *c != '\0'; c++) {
        switch(*c) {
        case '\0':
            break;
        case '-':
            enabled = rtsFalse;
            break;
        case 'a':
            RtsFlags.TraceFlags.scheduler      = enabled;
            RtsFlags.TraceFlags.gc             = enabled;
            RtsFlags.TraceFlags.sparks_sampled = enabled;
            RtsFlags.TraceFlags.sparks_full    = enabled;
            RtsFlags.TraceFlags.user           = enabled;
            enabled = rtsTrue;
            break;

        case 's':
            RtsFlags.TraceFlags.scheduler = enabled;
            enabled = rtsTrue;
            break;
        case 'p':
            RtsFlags.TraceFlags.sparks_sampled = enabled;
            enabled = rtsTrue;
            break;
        case 'f':
            RtsFlags.TraceFlags.sparks_full = enabled;
            enabled = rtsTrue;
            break;
        case 't':
            RtsFlags.TraceFlags.timestamp = enabled;
            enabled = rtsTrue;
            break;
        case 'g':
            RtsFlags.TraceFlags.gc        = enabled;
            enabled = rtsTrue;
            break;
        case 'u':
            RtsFlags.TraceFlags.user      = enabled;
            enabled = rtsTrue;
            break;
        default:
            errorBelch("unknown trace option: %c",*c);
            break;
        }
    }
}
