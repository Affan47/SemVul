static void bus_get_peercred(sd_bus *b) {
        int r;

        assert(b);
        assert(!b->ucred_valid);
        assert(!b->label);
        assert(b->n_groups == (size_t) -1);


        b->ucred_valid = getpeercred(b->input_fd, &b->ucred) >= 0;


        r = getpeersec(b->input_fd, &b->label);
        if (r < 0 && !IN_SET(r, -EOPNOTSUPP, -ENOPROTOOPT))
                log_debug_errno(r, "Failed to determine peer security context: %m");


        r = getpeergroups(b->input_fd, &b->groups);
        if (r >= 0)
                b->n_groups = (size_t) r;
        else if (!IN_SET(r, -EOPNOTSUPP, -ENOPROTOOPT))
                log_debug_errno(r, "Failed to determine peer's group list: %m");
}
