static int bus_socket_inotify_setup(sd_bus *b) {
        _cleanup_free_ int *new_watches = NULL;
        _cleanup_free_ char *absolute = NULL;
        size_t n_allocated = 0, n = 0, done = 0, i;
        unsigned max_follow = 32;
        const char *p;
        int wd, r;

        assert(b);
        assert(b->watch_bind);
        assert(b->sockaddr.sa.sa_family == AF_UNIX);
        assert(b->sockaddr.un.sun_path[0] != 0);


        if (b->inotify_fd < 0) {
                b->inotify_fd = inotify_init1(IN_NONBLOCK|IN_CLOEXEC);
                if (b->inotify_fd < 0)
                        return -errno;

                b->inotify_fd = fd_move_above_stdio(b->inotify_fd);
        }


        p = strndupa(b->sockaddr.un.sun_path, sizeof(b->sockaddr.un.sun_path));


        r = path_make_absolute_cwd(p, &absolute);
        if (r < 0)
                goto fail;


        if (!GREEDY_REALLOC(new_watches, n_allocated, n + 1)) {
                r = -ENOMEM;
                goto fail;
        }


        wd = inotify_add_watch(b->inotify_fd, "/", IN_CREATE|IN_MOVED_TO);
        if (wd < 0) {
                r = log_debug_errno(errno, "Failed to add inotify watch on /: %m");
                goto fail;
        } else
                new_watches[n++] = wd;

        for (;;) {
                _cleanup_free_ char *component = NULL, *prefix = NULL, *destination = NULL;
                size_t n_slashes, n_component;
                char *c = NULL;

                n_slashes = strspn(absolute + done, "/");
                n_component = n_slashes + strcspn(absolute + done + n_slashes, "/");

                if (n_component == 0)
                        break;

                component = strndup(absolute + done, n_component);
                if (!component) {
                        r = -ENOMEM;
                        goto fail;
                }


                if (path_equal(component, "/")) {
                        r = -EISDIR;
                        goto fail;
                }


                if (path_equal(component, "/.")) {
                        done += n_component;
                        continue;
                }

                prefix = strndup(absolute, done + n_component);
                if (!prefix) {
                        r = -ENOMEM;
                        goto fail;
                }

                if (!GREEDY_REALLOC(new_watches, n_allocated, n + 1)) {
                        r = -ENOMEM;
                        goto fail;
                }

                wd = inotify_add_watch(b->inotify_fd, prefix, IN_DELETE_SELF|IN_MOVE_SELF|IN_ATTRIB|IN_CREATE|IN_MOVED_TO|IN_DONT_FOLLOW);
                log_debug("Added inotify watch for %s on bus %s: %i", prefix, strna(b->description), wd);

                if (wd < 0) {
                        if (IN_SET(errno, ENOENT, ELOOP))
                                break;

                        r = log_debug_errno(errno, "Failed to add inotify watch on %s: %m", empty_to_root(prefix));
                        goto fail;
                } else
                        new_watches[n++] = wd;


                r = readlink_malloc(prefix, &destination);
                if (r == -EINVAL) {
                        done += n_component;
                        continue;
                }
                if (r < 0)
                        goto fail;

                if (isempty(destination)) {
                        r = -EINVAL;
                        goto fail;
                }

                if (max_follow <= 0) {
                        r = -ELOOP;
                        goto fail;
                }

                if (path_is_absolute(destination)) {

                        c = strjoin(destination, absolute + done + n_component);
                        done = 0;
                } else {
                        _cleanup_free_ char *t = NULL;


                        t = strndup(absolute, done);
                        if (!t)
                                return -ENOMEM;

                        c = strjoin(t, "/", destination, absolute + done + n_component);
                }
                if (!c) {
                        r = -ENOMEM;
                        goto fail;
                }

                free(absolute);
                absolute = c;

                max_follow--;
        }


        for (i = 0; i < b->n_inotify_watches; i++) {
                bool found = false;
                size_t j;

                for (j = 0; j < n; j++)
                        if (new_watches[j] == b->inotify_watches[i]) {
                                found = true;
                                break;
                        }

                if (found)
                        continue;

                (void) inotify_rm_watch(b->inotify_fd, b->inotify_watches[i]);
        }

        free_and_replace(b->inotify_watches, new_watches);
        b->n_inotify_watches = n;

        return 0;

fail:
        bus_close_inotify_fd(b);
        return r;
}
