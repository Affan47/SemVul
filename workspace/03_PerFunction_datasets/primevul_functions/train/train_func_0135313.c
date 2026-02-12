int vhost_vsock_common_pre_save(void *opaque)
{
    VHostVSockCommon *vvc = opaque;


    assert(!vvc->vhost_dev.started);

    return 0;
}
