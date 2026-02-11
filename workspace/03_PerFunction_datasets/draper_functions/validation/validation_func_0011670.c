omega_delete_geq (omega_pb pb, int e, int n_vars)
{
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Deleting %d (last:%d): ", e, pb->num_geqs - 1);
      omega_print_geq (dump_file, pb, &pb->geqs[e]);
      fprintf (dump_file, "\n");
    }

  if (e < pb->num_geqs - 1)
    omega_copy_eqn (&pb->geqs[e], &pb->geqs[pb->num_geqs - 1], n_vars);

  pb->num_geqs--;
}
