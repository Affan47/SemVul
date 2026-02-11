_PrintTree(vtkKdNode *kd, int depth)
{
  kd->PrintNode(depth);

  if (kd->GetLeft())
    {
    vtkBSPCuts::_PrintTree(kd->GetLeft(),depth+1);
    vtkBSPCuts::_PrintTree(kd->GetRight(),depth+1);
    }
}
