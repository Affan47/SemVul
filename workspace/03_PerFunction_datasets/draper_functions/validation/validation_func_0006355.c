release_single_user_lock()
{
    if (d_locked_open_file) {
        int res = fclose(d_locked_open_file);
        if (res) {
            DBG(cerr << "Failed to close " << (void *)d_locked_open_file << endl) ;
        }
        d_locked_open_file = 0;
    }

    string lock = d_cache_root + CACHE_LOCK;
    REMOVE(lock.c_str());
}
