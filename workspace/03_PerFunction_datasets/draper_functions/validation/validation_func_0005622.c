add_resource(const char *fname, size_t fnamelen,
                                  const char *resname, size_t resnamelen)
{
    CResEntry *entry;


    entry = new CResEntry(resname, resnamelen, TRUE, fname, fnamelen);


    restab_->add(entry);
}
