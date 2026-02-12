hp_compute_dev (struct cpio_file_stat *file_hdr, dev_t *pdev, dev_t *prdev)
{


  switch (file_hdr->c_mode & CP_IFMT)
    {
    case CP_IFCHR:
    case CP_IFBLK:
#ifdef CP_IFSOCK
    case CP_IFSOCK:
#endif
#ifdef CP_IFIFO
    case CP_IFIFO:
#endif
      file_hdr->c_filesize = makedev (file_hdr->c_rdev_maj,
				      file_hdr->c_rdev_min);
      *pdev = *prdev = makedev (0, 1);
      break;

    default:
      *pdev = makedev (file_hdr->c_dev_maj, file_hdr->c_dev_min);
      *prdev = makedev (file_hdr->c_rdev_maj, file_hdr->c_rdev_min);
      break;
    }
}
