__inode_table_init_root (inode_table_t *table)
{
        inode_t     *root = NULL;
        struct iatt  iatt = {0, };

        if (!table)
                return;

        root = __inode_create (table);

        iatt.ia_gfid[15] = 1;
        iatt.ia_ino = 1;
        iatt.ia_type = IA_IFDIR;

        __inode_link (root, NULL, NULL, &iatt);
        table->root = root;
}
