GetLinedefs(void)
{
  int i, count=-1;
  raw_linedef_t *raw;
  lump_t *lump = FindLevelLump("LINEDEFS");

  if (lump)
    count = lump->length / sizeof(raw_linedef_t);

  if (!lump || count == 0)
    FatalError("Couldn't find any Linedefs");

  DisplayTicker();

# if DEBUG_LOAD
  PrintDebug("GetLinedefs: num = %d\n", count);
# endif

  raw = (raw_linedef_t *) lump->data;

  for (i=0; i < count; i++, raw++)
  {
    linedef_t *line;

    vertex_t *start = LookupVertex(UINT16(raw->start));
    vertex_t *end   = LookupVertex(UINT16(raw->end));

    start->ref_count++;
    end->ref_count++;

    line = NewLinedef();

    line->start = start;
    line->end   = end;


    line->zero_len = (fabs(start->x - end->x) < DIST_EPSILON) &&
        (fabs(start->y - end->y) < DIST_EPSILON);

    line->flags = UINT16(raw->flags);
    line->type = UINT16(raw->type);
    line->tag  = SINT16(raw->tag);

    line->two_sided = (line->flags & LINEFLAG_TWO_SIDED) ? TRUE : FALSE;
    line->is_precious = (line->tag >= 900 && line->tag < 1000) ?
        TRUE : FALSE;

    line->right = SafeLookupSidedef(UINT16(raw->sidedef1));
    line->left  = SafeLookupSidedef(UINT16(raw->sidedef2));

    if (line->right)
    {
      line->right->ref_count++;
      line->right->on_special |= (line->type > 0) ? 1 : 0;
    }

    if (line->left)
    {
      line->left->ref_count++;
      line->left->on_special |= (line->type > 0) ? 1 : 0;
    }

    line->self_ref = (line->left && line->right &&
        (line->left->sector == line->right->sector));

    line->index = i;
  }
}
