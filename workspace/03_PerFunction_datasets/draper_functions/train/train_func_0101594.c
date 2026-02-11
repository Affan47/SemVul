__createMesh()
{
  ReferenceCounting<VerticesCorrespondance> correspondance
    = new VerticesCorrespondance((*__vertices).numberOfVertices());

  if (__hexahedra != 0) {
    SurfaceMeshOfQuadrangles* quadrilaterals = 0;
    if (__quadrilaterals != 0) {
      quadrilaterals = new SurfaceMeshOfQuadrangles(__vertices,
						    correspondance,
						    __quadrilaterals);
    }
    MeshOfHexahedra* m
      = new MeshOfHexahedra(__vertices,
			    correspondance,
			    __hexahedra,
			    quadrilaterals);
    __mesh = m;
    ffout(3) << "- Number of Hexahedra: " << (*__hexahedra).size() << '\n';
    return;
  }


  if (__tetrahedra != 0) {
    SurfaceMeshOfTriangles* triangles = 0;
    if (__triangles != 0) {
      triangles = new SurfaceMeshOfTriangles(__vertices,
					     correspondance,
					     __triangles);
    }
    MeshOfTetrahedra* m
      = new MeshOfTetrahedra(__vertices,
			     correspondance,
			     __tetrahedra,
			     triangles);
    __mesh = m;
    ffout(3) << "- Number of Tetrahedra: " << (*__tetrahedra).size() << '\n';
    return;
  }

  if (__triangles != 0) {
    for (size_t i=0; i<__vertices->numberOfVertices();++i) {
      const Vertex& v = (*__vertices)[i];
      if (v[2] != 0) {
	SurfaceMeshOfTriangles* m
	  = new SurfaceMeshOfTriangles(__vertices,
				       correspondance,
				       __triangles);
	__mesh = m;
	ffout(3) << "- Number of Triangles: " << __triangles->size() << '\n';
	return;
      }
    }

    MeshOfTriangles* m
      = new MeshOfTriangles(__vertices,
			    correspondance,
			    __triangles);
    __mesh = m;
    ffout(3) << "- Number of Triangles: " << __triangles->size() << '\n';
    return;
  }

  if (__quadrilaterals != 0) {
    SurfaceMeshOfQuadrangles* m
      = new SurfaceMeshOfQuadrangles(__vertices,
				     correspondance,
				     __quadrilaterals);
    __mesh = m;
    ffout(3) << "- Number of Quadrilaterals: " << (*__quadrilaterals).size() << '\n';
    return;
  }
}
