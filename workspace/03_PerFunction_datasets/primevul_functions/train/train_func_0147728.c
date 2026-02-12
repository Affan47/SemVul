KaxBlockVirtual::KaxBlockVirtual(const KaxBlockVirtual & ElementToClone)
  :EbmlBinary(ElementToClone)
  ,Timecode(ElementToClone.Timecode)
  ,TrackNumber(ElementToClone.TrackNumber)
  ,ParentCluster(ElementToClone.ParentCluster)
{
  SetBuffer(DataBlock,sizeof(DataBlock));
  SetValueIsSet(false);
}
