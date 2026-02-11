populate_rootfs(void)
{
	char *err = unpack_to_rootfs(__initramfs_start, __initramfs_size);
	if (err)
		panic("%s", err);
	if (initrd_start) {
#ifdef CONFIG_BLK_DEV_RAM
		int fd;
		printk(KERN_INFO "Trying to unpack rootfs image as initramfs...\n");
		err = unpack_to_rootfs((char *)initrd_start,
			initrd_end - initrd_start);
		if (!err) {
			free_initrd();
			goto done;
		} else {
			clean_rootfs();
			unpack_to_rootfs(__initramfs_start, __initramfs_size);
		}
		printk(KERN_INFO "rootfs image is not initramfs (%s)"
				"; looks like an initrd\n", err);
		fd = sys_open("/initrd.image",
			      O_WRONLY|O_CREAT, 0700);
		if (fd >= 0) {
			ssize_t written = xwrite(fd, (char *)initrd_start,
						initrd_end - initrd_start);

			if (written != initrd_end - initrd_start)
				pr_err("/initrd.image: incomplete write (%zd != %ld)\n",
				       written, initrd_end - initrd_start);

			sys_close(fd);
			free_initrd();
		}
	done:
#else
		printk(KERN_INFO "Unpacking initramfs...\n");
		err = unpack_to_rootfs((char *)initrd_start,
			initrd_end - initrd_start);
		if (err)
			printk(KERN_EMERG "Initramfs unpacking failed: %s\n", err);
		free_initrd();
#endif


		load_default_modules();
	}
	return 0;
}
