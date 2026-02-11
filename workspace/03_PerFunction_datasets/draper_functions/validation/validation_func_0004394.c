PutOneV5Node(node_t *node, lump_t *lump)
{
  raw_v5_node_t raw;

  if (node->r.node)
    PutOneV5Node(node->r.node, lump);

  if (node->l.node)
    PutOneV5Node(node->l.node, lump);

  node->index = node_cur_index++;

  raw.x  = SINT16(node->x);
  raw.y  = SINT16(node->y);
  raw.dx = SINT16(node->dx / (node->too_long ? 2 : 1));
  raw.dy = SINT16(node->dy / (node->too_long ? 2 : 1));

  raw.b1.minx = SINT16(node->r.bounds.minx);
  raw.b1.miny = SINT16(node->r.bounds.miny);
  raw.b1.maxx = SINT16(node->r.bounds.maxx);
  raw.b1.maxy = SINT16(node->r.bounds.maxy);

  raw.b2.minx = SINT16(node->l.bounds.minx);
  raw.b2.miny = SINT16(node->l.bounds.miny);
  raw.b2.maxx = SINT16(node->l.bounds.maxx);
  raw.b2.maxy = SINT16(node->l.bounds.maxy);

  if (node->r.node)
    raw.right = UINT32(node->r.node->index);
  else if (node->r.subsec)
    raw.right = UINT32(node->r.subsec->index | 0x80000000U);
  else
    InternalError("Bad right child in V5 node %d", node->index);

  if (node->l.node)
    raw.left = UINT32(node->l.node->index);
  else if (node->l.subsec)
    raw.left = UINT32(node->l.subsec->index | 0x80000000U);
  else
    InternalError("Bad left child in V5 node %d", node->index);

  AppendLevelLump(lump, &raw, sizeof(raw));

# if DEBUG_BSP
  PrintDebug("PUT V5 NODE %08X  Left %08X  Right %08X  "
    "(%d,%d) -> (%d,%d)\n", node->index, UINT32(raw.left),
    UINT32(raw.right), node->x, node->y,
    node->x + node->dx, node->y + node->dy);
# endif
}
