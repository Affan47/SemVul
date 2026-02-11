cli_print_detailed_status (cli_volume_status_t *status)
{
        cli_out ("%-20s : %-20s", "Brick", status->brick);
        cli_out ("%-20s : %-20d", "Port", status->port);
        cli_out ("%-20s : %-20c", "Online", (status->online) ? 'Y' : 'N');
        cli_out ("%-20s : %-20s", "Pid", status->pid_str);
        cli_out ("%-20s : %-20s", "File System", status->fs_name);
        cli_out ("%-20s : %-20s", "Device", status->device);

        if (status->mount_options) {
                cli_out ("%-20s : %-20s", "Mount Options",
                         status->mount_options);
        } else {
                cli_out ("%-20s : %-20s", "Mount Options", "N/A");
        }

        cli_out ("%-20s : %-20s", "Disk Space Free", status->free);
        cli_out ("%-20s : %-20s", "Total Disk Space", status->total);

        if (status->inode_size) {
                cli_out ("%-20s : %-20s", "Inode Size",
                         status->inode_size);
        } else {
                cli_out ("%-20s : %-20s", "Inode Size", "N/A");
        }

        if (status->total_inodes) {
                cli_out ("%-20s : %-20ld", "Inode Count",
                         status->total_inodes);
        } else {
                cli_out ("%-20s : %-20s", "Inode Count", "N/A");
        }

        if (status->free_inodes) {
                cli_out ("%-20s : %-20ld", "Free Inodes",
                         status->free_inodes);
        } else {
                cli_out ("%-20s : %-20s", "Free Inodes", "N/A");
        }
}
