virSecuritySELinuxRestoreSCSILabel(virSCSIDevice *dev,
                                   const char *file,
                                   void *opaque)
{
    virSecurityManager *mgr = opaque;


    if (virSCSIDeviceGetShareable(dev) || virSCSIDeviceGetReadonly(dev))
        return 0;

    return virSecuritySELinuxRestoreFileLabel(mgr, file, true);
}
