hb_ot_layout_get_attach_points (hb_face_t      *face,
				hb_codepoint_t  glyph,
				unsigned int   *point_count ,
				unsigned int   *point_array )
{
  return _get_gdef (face).get_attach_points (glyph, point_count, point_array);
}
