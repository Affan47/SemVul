saveObj(std::string filename) {

  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<std::vector<int> > faces;
  for (int i=0; i<bezObjs[0].size(); i++) {
    int offset = points.size();
    int tempFace[3];

    std::vector<std::vector<int> > tempFaces = bezObjs[0][i].getFaces();
    for (int j=0; j<tempFaces.size(); j++) {
      for (int k=0; k<3; k++) {
        tempFace[k] = tempFaces[j][k] + offset;
      }
      faces.push_back(std::vector<int>(tempFace,tempFace+3));
    }

    std::vector<Vertex> tempVertices = bezObjs[0][i].getVertices();
    for (int j=0; j<tempVertices.size(); j++) {
      points.push_back(tempVertices[j].pos());
      normals.push_back(tempVertices[j].normal());
    }
  }

  std::ofstream objFile;
  objFile.open (filename.c_str());
  for (int i=0; i<points.size(); i++){
    objFile << "v " << points[i][0] << " " << points[i][1] << " " << points[i][2] << "\n";
  }
  for (int i=0; i<normals.size(); i++){
    objFile << "vn " << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << "\n";
  }
  for (int i=0; i<faces.size(); i++){
    objFile << "f";
    for (int j=0; j<3; j++){
      objFile << " " << faces[i][j]+1 << "//" << faces[i][j]+1;
    }
    objFile << "\n";
  }
  objFile.close();

}
