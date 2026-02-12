bool update_NeedUpgrade( update_t *p_update )
{
    assert( p_update );

    static const int current[4] = {
        PACKAGE_VERSION_MAJOR,
        PACKAGE_VERSION_MINOR,
        PACKAGE_VERSION_REVISION,
        PACKAGE_VERSION_EXTRA
    };
    const int latest[4] = {
        p_update->release.i_major,
        p_update->release.i_minor,
        p_update->release.i_revision,
        p_update->release.i_extra
    };

    for (unsigned i = 0; i < sizeof latest / sizeof *latest; i++) {

        if (latest[i] > current[i])
            return true;


        if (latest[i] < current[i])
            return false;
    }


    if (*PACKAGE_VERSION_DEV)
        return true;


    return false;
}
