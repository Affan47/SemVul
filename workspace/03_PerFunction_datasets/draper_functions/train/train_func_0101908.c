close_au(krb5_audit_moddata auctx)
{
    fclose(au_fd);
    k5_mutex_destroy(&lock);
    return 0;
}
