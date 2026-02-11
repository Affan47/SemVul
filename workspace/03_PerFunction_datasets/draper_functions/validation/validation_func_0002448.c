umap_basic_basic_eq(const umap_basic_basic &a,
        const umap_basic_basic &b)
{


    if (a.size() != b.size()) return false;

    for (auto &p: a) {

        auto f = b.find(p.first);
        if (f == b.end()) return false;
        if (neq(p.second, f->second)) return false;
    }
    return true;
}
