gf_roundup_power_of_two (uint32_t nr)
{
        uint32_t result = 1;

        if (nr < 0) {
                gf_log ("common-utils", GF_LOG_WARNING,
                        "negative number passed");
                result = -1;
                goto out;
        }

        while (result < nr)
                result *= 2;

out:
        return result;
}
