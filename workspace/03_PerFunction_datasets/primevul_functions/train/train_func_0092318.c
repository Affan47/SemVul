static void update_open_flags(int writeback, int allow_direct_io,
                              struct fuse_file_info *fi)
{


    if (writeback && (fi->flags & O_ACCMODE) == O_WRONLY) {
        fi->flags &= ~O_ACCMODE;
        fi->flags |= O_RDWR;
    }


    if (writeback && (fi->flags & O_APPEND)) {
        fi->flags &= ~O_APPEND;
    }


    if (!allow_direct_io) {
        fi->flags &= ~O_DIRECT;
    }
}
