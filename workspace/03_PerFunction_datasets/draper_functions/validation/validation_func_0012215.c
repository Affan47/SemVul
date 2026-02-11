WriteProtected () {
    ModifStatusVar* msv = (ModifStatusVar*) _subject;
    Catalog* catalog = unidraw->GetCatalog();
    const char* name = catalog->GetName(msv->GetComponent());
    return name != nil &&  catalog->Exists(name) && !catalog->Writable(name);
}
