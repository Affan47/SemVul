ProcessParam1BeforeParam2(IntersectNode &node1, IntersectNode &node2)
{
  bool result;
  if (node1.pt.Y == node2.pt.Y)
  {
    if (node1.edge1 == node2.edge1 || node1.edge2 == node2.edge1)
    {
      result = node2.pt.X > node1.pt.X;
      return node2.edge1->dx > 0 ? !result : result;
    }
    else if (node1.edge1 == node2.edge2 || node1.edge2 == node2.edge2)
    {
      result = node2.pt.X > node1.pt.X;
      return node2.edge2->dx > 0 ? !result : result;
    }
    else return node2.pt.X > node1.pt.X;
  }
  else return node1.pt.Y > node2.pt.Y;
}
