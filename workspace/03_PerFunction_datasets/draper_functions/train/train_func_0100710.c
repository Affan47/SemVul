udf_new_dirent(udf_file_entry_t *p_udf_fe, udf_t *p_udf,
	       const char *psz_name, bool b_dir, bool b_parent)
{
  const unsigned int i_alloc_size = p_udf_fe->i_alloc_descs
    + p_udf_fe->i_extended_attr;

  udf_dirent_t *p_udf_dirent = (udf_dirent_t *)
    calloc(1, sizeof(udf_dirent_t) + i_alloc_size);
  if (!p_udf_dirent) return NULL;

  p_udf_dirent->psz_name     = strdup(psz_name);
  p_udf_dirent->b_dir        = b_dir;
  p_udf_dirent->b_parent     = b_parent;
  p_udf_dirent->p_udf        = p_udf;
  p_udf_dirent->i_part_start = p_udf->i_part_start;
  p_udf_dirent->dir_left     = uint64_from_le(p_udf_fe->info_len);

  memcpy(&(p_udf_dirent->fe), p_udf_fe,
	 sizeof(udf_file_entry_t) + i_alloc_size);
  udf_get_lba( p_udf_fe, &(p_udf_dirent->i_loc),
	       &(p_udf_dirent->i_loc_end) );
  return p_udf_dirent;
}
