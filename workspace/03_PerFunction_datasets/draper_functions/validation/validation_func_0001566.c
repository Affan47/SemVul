fn_for_generation(char *buf, char *base, char *ext, f_i64 gen)
{
    if (-1 == gen) {
        return NULL;
    }
    else {
        char b[SEGMENT_NAME_MAX_LENGTH];
        char *u = u64_to_str36(b, SEGMENT_NAME_MAX_LENGTH, (f_u64)gen);
        if (ext == NULL) {
            sprintf(buf, "%s_%s", base, u);
        }
        else {
            sprintf(buf, "%s_%s.%s", base, u, ext);
        }
        return buf;
    }
}
