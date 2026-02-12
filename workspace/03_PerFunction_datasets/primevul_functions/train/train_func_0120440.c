parse_range_dec64(const char **str_num, uint8_t dig, int64_t *num)
{
    const char *ptr;
    int minus = 0;
    int64_t ret = 0, prev_ret;
    int8_t str_exp, str_dig = -1, trailing_zeros = 0;

    ptr = *str_num;

    if (ptr[0] == '-') {
        minus = 1;
        ++ptr;
    } else if (ptr[0] == '+') {
        ++ptr;
    }

    if (!isdigit(ptr[0])) {

        return 1;
    }

    for (str_exp = 0; isdigit(ptr[0]) || ((ptr[0] == '.') && (str_dig < 0)); ++ptr) {
        if (str_exp > 18) {
            return 1;
        }

        if (ptr[0] == '.') {
            if (ptr[1] == '.') {

                break;
            }
            ++str_dig;
        } else {
            prev_ret = ret;
            if (minus) {
                ret = ret * 10 - (ptr[0] - '0');
                if (ret > prev_ret) {
                    return 1;
                }
            } else {
                ret = ret * 10 + (ptr[0] - '0');
                if (ret < prev_ret) {
                    return 1;
                }
            }
            if (str_dig > -1) {
                ++str_dig;
                if (ptr[0] == '0') {

                    trailing_zeros++;
                } else {
                    trailing_zeros = 0;
                }
            }
            ++str_exp;
        }
    }
    if (str_dig == 0) {

        return 1;
    } else if (str_dig == -1) {

        str_dig = 0;
    }

    if (trailing_zeros) {
        str_dig -= trailing_zeros;
        str_exp -= trailing_zeros;
        ret = ret / dec_pow(trailing_zeros);
    }


    if (str_dig < dig) {
        if ((str_exp - 1) + (dig - str_dig) > 18) {
            return 1;
        }
        prev_ret = ret;
        ret *= dec_pow(dig - str_dig);
        if ((minus && (ret > prev_ret)) || (!minus && (ret < prev_ret))) {
            return 1;
        }

    }
    if (str_dig > dig) {
        return 1;
    }

    *str_num = ptr;
    *num = ret;

    return 0;
}
