static int not_resumable_sess_cb(SSL *s, int is_forward_secure)
{

    return is_forward_secure;
}
