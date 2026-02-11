av_arch_isroot(struct archive *arch, struct entry *ent)
{
    int res;
    struct entry *root;

    root = av_namespace_subdir(arch->ns, NULL);
    if(root == ent)
        res = 1;
    else
        res = 0;

    av_unref_obj(root);

    return res;
}
