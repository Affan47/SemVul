disqualify_candidate (tree decl, const char *reason)
{
  if (bitmap_clear_bit (candidate_bitmap, DECL_UID (decl)))
    htab_clear_slot (candidates,
		     htab_find_slot_with_hash (candidates, decl,
					       DECL_UID (decl), NO_INSERT));

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "! Disqualifying ");
      print_generic_expr (dump_file, decl, 0);
      fprintf (dump_file, " - %s\n", reason);
    }
}
