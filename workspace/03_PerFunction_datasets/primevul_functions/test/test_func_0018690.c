int ram_block_discard_range(struct uc_struct *uc, RAMBlock *rb, uint64_t start, size_t length)
{
    int ret = -1;

    uint8_t *host_startaddr = rb->host + start;

    if (!QEMU_PTR_IS_ALIGNED(host_startaddr, rb->page_size)) {


        goto err;
    }

    if ((start + length) <= rb->used_length) {
        bool need_madvise;
        if (!QEMU_IS_ALIGNED(length, rb->page_size)) {


            goto err;
        }

        errno = ENOTSUP;


        need_madvise = (rb->page_size == uc->qemu_host_page_size);
        if (need_madvise) {


#if defined(CONFIG_MADVISE)
            ret =  madvise(host_startaddr, length, MADV_DONTNEED);
            if (ret) {
                ret = -errno;


                goto err;
            }
#else
            ret = -ENOSYS;


            goto err;
#endif
        }
    } else {


    }

err:
    return ret;
}
