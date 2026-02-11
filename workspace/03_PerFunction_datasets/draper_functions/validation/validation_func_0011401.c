posix_fill_readdir (fd_t *fd, DIR *dir, off_t off, size_t size,
                    gf_dirent_t *entries)
{
        off_t     in_case = -1;
        size_t    filled = 0;
        int             count = 0;
        char      entrybuf[sizeof(struct dirent) + 256 + 8];
        struct dirent  *entry          = NULL;
        int32_t               this_size      = -1;
        gf_dirent_t          *this_entry     = NULL;
        uuid_t                rootgfid = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

        if (!off) {
                rewinddir (dir);
        } else {
                seekdir (dir, off);
        }

        while (filled <= size) {
                in_case = telldir (dir);

                if (in_case == -1) {
                        gf_log (THIS->name, GF_LOG_ERROR,
                                "telldir failed on dir=%p: %s",
                                dir, strerror (errno));
                        goto out;
                }

                errno = 0;
                entry = NULL;
                readdir_r (dir, (struct dirent *)entrybuf, &entry);

                if (!entry) {
                        if (errno == EBADF) {
                                gf_log (THIS->name, GF_LOG_WARNING,
                                        "readdir failed on dir=%p: %s",
                                        dir, strerror (errno));
                                goto out;
                        }
                        break;
                }

                if ((uuid_compare (fd->inode->gfid, rootgfid) == 0)
                    && (!strcmp (entry->d_name, GF_REPLICATE_TRASH_DIR)))
                        continue;

#ifdef __NetBSD__


		if ((uuid_compare (fd->inode->gfid, rootgfid) == 0)
		    && (!strcmp(entry->d_name, ".attribute")))
			continue;
#endif

                if ((uuid_compare (fd->inode->gfid, rootgfid) == 0)
                    && (!strncmp (GF_HIDDEN_PATH, entry->d_name,
                                  strlen (GF_HIDDEN_PATH)))) {
                        continue;
                }

                this_size = max (sizeof (gf_dirent_t),
                                 sizeof (gfs3_dirplist))
                        + strlen (entry->d_name) + 1;

                if (this_size + filled > size) {
                        seekdir (dir, in_case);
                        break;
                }

                this_entry = gf_dirent_for_name (entry->d_name);

                if (!this_entry) {
                        gf_log (THIS->name, GF_LOG_ERROR,
                                "could not create gf_dirent for entry %s: (%s)",
                                entry->d_name, strerror (errno));
                        goto out;
                }
                this_entry->d_off = telldir (dir);
                this_entry->d_ino = entry->d_ino;

                list_add_tail (&this_entry->list, &entries->list);

                filled += this_size;
                count ++;
        }

        if ((!readdir (dir) && (errno == 0)))

                errno = ENOENT;
out:
        return count;
}
