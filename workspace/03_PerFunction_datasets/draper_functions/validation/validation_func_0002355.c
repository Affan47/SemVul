AppendCells(vtkIdType *pDest, vtkCellArray *src,
                                          vtkIdType offset)
{
  vtkIdType *pSrc, *end, *pNum;

  if (src == NULL)
    {
    return pDest;
    }

  pSrc = src->GetPointer();
  end = pSrc + src->GetNumberOfConnectivityEntries();
  pNum = pSrc;

  while (pSrc < end)
    {
    if (pSrc == pNum)
      {

      pNum += 1+*pSrc;

      *pDest++ = *pSrc++;
      }
    else
      {

      *pDest++ = offset + *pSrc++;
      }
    }

  return pDest;
}
