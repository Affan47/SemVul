lvuuid_stub (XDR *xdr_in)
{
  char *r;
  struct guestfs_lvuuid_args args;
  CLEANUP_FREE char *device = NULL;

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_lvuuid_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  RESOLVE_DEVICE (args.device, device, , goto done);

  r = do_lvuuid (device);
  if (r == NULL)

    goto done;

  struct guestfs_lvuuid_ret ret;
  ret.uuid = r;
  reply ((xdrproc_t) &xdr_guestfs_lvuuid_ret, (char *) &ret);
  free (r);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_lvuuid_args, (char *) &args);
done_no_free:
  return;
}
