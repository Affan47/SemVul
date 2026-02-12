static void unit_unref_uid_internal(
                Unit *u,
                uid_t *ref_uid,
                bool destroy_now,
                void (*_manager_unref_uid)(Manager *m, uid_t uid, bool destroy_now)) {

        assert(u);
        assert(ref_uid);
        assert(_manager_unref_uid);


        assert_cc(sizeof(uid_t) == sizeof(gid_t));
        assert_cc(UID_INVALID == (uid_t) GID_INVALID);

        if (!uid_is_valid(*ref_uid))
                return;

        _manager_unref_uid(u->manager, *ref_uid, destroy_now);
        *ref_uid = UID_INVALID;
}
