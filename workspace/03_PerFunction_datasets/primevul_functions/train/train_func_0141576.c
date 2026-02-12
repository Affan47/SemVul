Error Box_dref::parse(BitstreamRange& range)
{
  parse_full_box_header(range);

  int nEntities = range.read32();


  Error err = read_children(range, nEntities);
  if (err) {
    return err;
  }

  if ((int)m_children.size() != nEntities) {

  }

  return err;
}
