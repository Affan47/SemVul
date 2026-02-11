accepts(void *data)
{
    bool pass = true;
    char *act_string = _column->getValue(data);
    switch (_opid) {
        case OP_EQUAL:
            pass = _ref_string == act_string; break;
        case OP_EQUAL_ICASE:
            pass = !strcasecmp(_ref_string.c_str(), act_string); break;
        case OP_REGEX:
        case OP_REGEX_ICASE:
            pass = _regex != 0 && 0 == regexec(_regex, act_string, 0, 0, 0);
            break;
        case OP_GREATER:
            pass = 0 > strcmp(_ref_string.c_str(), act_string); break;
        case OP_LESS:
            pass = 0 < strcmp(_ref_string.c_str(), act_string); break;
        default:

            logger(LG_INFO, "Sorry. Operator %s for strings not implemented.", op_names_plus_8[_opid]);
            break;
    }
    return pass != _negate;
}
