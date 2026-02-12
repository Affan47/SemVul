void Statement::Finalize_() {
    assert(!finalized);
    finalized = true;
    CleanQueue();


    sqlite3_finalize(_handle);
    _handle = NULL;
    db->Unref();
}
