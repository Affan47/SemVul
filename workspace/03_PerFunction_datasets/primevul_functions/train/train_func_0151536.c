inline void init (hb_face_t *face)
  {
    this->blob = OT::Sanitizer<OT::cmap>::sanitize (face->reference_table (HB_OT_TAG_cmap));
    const OT::cmap *cmap = OT::Sanitizer<OT::cmap>::lock_instance (this->blob);
    const OT::CmapSubtable *subtable = NULL;
    const OT::CmapSubtable *subtable_uvs = NULL;


    if (!subtable) subtable = cmap->find_subtable (3, 10);
    if (!subtable) subtable = cmap->find_subtable (0, 6);
    if (!subtable) subtable = cmap->find_subtable (0, 4);

    if (!subtable) subtable = cmap->find_subtable (3, 1);
    if (!subtable) subtable = cmap->find_subtable (0, 3);
    if (!subtable) subtable = cmap->find_subtable (0, 2);
    if (!subtable) subtable = cmap->find_subtable (0, 1);
    if (!subtable) subtable = cmap->find_subtable (0, 0);
    if (!subtable) subtable = cmap->find_subtable (3, 0);

    if (!subtable) subtable = &OT::Null(OT::CmapSubtable);


    if (!subtable_uvs) subtable_uvs = cmap->find_subtable (0, 5);

    if (!subtable_uvs) subtable_uvs = &OT::Null(OT::CmapSubtable);

    this->table = subtable;
    this->uvs_table = subtable_uvs;
  }
