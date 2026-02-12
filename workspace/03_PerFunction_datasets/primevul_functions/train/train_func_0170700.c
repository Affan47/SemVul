static int init_sig_algs_cert(SSL *s, unsigned int context)
{

    OPENSSL_free(s->s3->tmp.peer_cert_sigalgs);
    s->s3->tmp.peer_cert_sigalgs = NULL;

    return 1;
}
