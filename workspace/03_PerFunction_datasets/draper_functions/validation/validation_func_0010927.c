mpegts_base_apply_pmt (MpegTSBase * base,
    guint16 pmt_pid, GstStructure * pmt_info)
{
  MpegTSBaseProgram *program, *old_program;
  guint program_number;
  gboolean deactivate_old_program = FALSE;


  if (G_UNLIKELY (base->seen_pat == FALSE)) {
    GST_WARNING ("Got pmt without pat first. Returning");

    mpegts_packetizer_remove_stream (base->packetizer, pmt_pid);
    return;
  }

  gst_structure_id_get (pmt_info, QUARK_PROGRAM_NUMBER, G_TYPE_UINT,
      &program_number, NULL);

  GST_DEBUG ("Applying PMT (program_number:%d, pid:0x%04x)",
      program_number, pmt_pid);


  old_program = mpegts_base_get_program (base, program_number);
  if (G_UNLIKELY (old_program == NULL))
    goto no_program;


  if (old_program->active) {
    old_program = mpegts_base_steal_program (base, program_number);
    program = mpegts_base_new_program (base, program_number, pmt_pid);
    g_hash_table_insert (base->programs,
        GINT_TO_POINTER (program_number), program);
    deactivate_old_program = TRUE;
  } else
    program = old_program;


  mpegts_base_activate_program (base, program, pmt_pid, pmt_info);

  if (deactivate_old_program) {
     ;
    mpegts_base_deactivate_program (base, old_program);
    mpegts_base_free_program (old_program);
  }


  gst_element_post_message (GST_ELEMENT_CAST (base),
      gst_message_new_element (GST_OBJECT (base),
          gst_structure_copy (pmt_info)));

  return;

no_program:
  {
    GST_ERROR ("Attempted to apply a PMT on a program that wasn't created");
    return;
  }
}
