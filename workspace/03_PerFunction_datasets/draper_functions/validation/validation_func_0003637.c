nt_build_sai_string_by_hash(const char *key, long val, void *cd_sai_builder) {
    struct SAI_string_builder *sai_builder = (struct SAI_string_builder*)cd_sai_builder;

    const char *sep = strchr(key,1);
    if (!sep) return val;

    struct GBS_strstruct *sai_middle      = sai_builder->sai_middle;
    const char           *last_group_name = sai_builder->last_group_name;

    if (!last_group_name || strncmp(key, last_group_name, sep-key)) {
        if (last_group_name){
            GBS_chrcat(sai_middle,1);
            GBS_chrcat(sai_middle,'E');
        }
        GBS_chrcat(sai_middle,1);
        GBS_strcat(sai_middle,"FSAI:");
        GBS_strncat(sai_middle,key,sep-key);
        sai_builder->last_group_name = key;
    }
    GBS_chrcat(sai_middle,1);
    GBS_strcat(sai_middle,"S");
    GBS_strcat(sai_middle,sep+1);
    return val;
}
