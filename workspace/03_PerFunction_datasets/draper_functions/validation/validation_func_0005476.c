removeLayers()
{
  for (int i = 0; i < nofLayers; i++) {

    delete belements[i];
    delete boundboxes[i];
    delete elementLoopIds[i];
    delete elementLoopTags[i];
    delete pendingElementTags[i];
    delete pendingVertexGroups[i];
    delete pendingVertexTags[i];
  }

  nofLayers = 0;

  delete[] belements;
  delete[] elementLoopIds;
  delete[] elementLoopTags;
  delete[] layerIds;
  delete[] nofElements;
  delete[] nofElementLoops;
  delete[] nofInnerBoundaries;
  delete[] nofOuterBoundaries;
}
