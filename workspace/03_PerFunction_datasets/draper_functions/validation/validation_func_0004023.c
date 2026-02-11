apic_load (struct qemu_device *d, FILE *fp, enum qemu_save_section sec)
{
	switch (d->version_id) {
	case 1: fseek (fp, 173, SEEK_CUR); break;
	case 2:
	case 3: fseek (fp, 181, SEEK_CUR); break;
	}

	return 0;
}
