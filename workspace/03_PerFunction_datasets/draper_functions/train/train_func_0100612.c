copyElement(const DcmTagKey& tag, DcmItem& src, DcmItem& dest)
{
  DcmElement *delem;
  OFCondition cond;

  cond = src.findAndGetElement(tag, delem, OFFalse , OFTrue );
  if (cond.good())
  {

    cond = dest.insert(delem, OFTrue);
    if (cond.bad())
    {

      DCMDATA_ERROR("Could not insert element with tag " << tag << " into item: " << cond.text());
    }
  }
}
