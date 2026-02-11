getnum(cchar *value)
{
    int64   num;

    value = strim(slower(value), " \t", MPR_TRIM_BOTH);
    if (sends(value, "k") || sends(value, "KB")) {
        num = stoi(value) * 1024;
    } else if (sends(value, "mb") || sends(value, "M")) {
        num = stoi(value) * 1024 * 1024;
    } else if (sends(value, "gb") || sends(value, "G")) {
        num = stoi(value) * 1024 * 1024 * 1024;
    } else {
        num = stoi(value);
    }
    return num;
}
