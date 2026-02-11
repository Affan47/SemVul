setVertices(const hsTArray<TempVertex>& verts) {
    fVertexData.clear();
    fDiffuseRGBA.clear();
    fSpecularRGBA.clear();
    fMultColor.clear();
    fAddColor.clear();

    unsigned int stride = CalcVertexSize(fFormat);
    fNumVerts = verts.getSize();
    fVertexData.setSize(fNumVerts * stride);
    fDiffuseRGBA.setSize(fNumVerts);
    fSpecularRGBA.setSize(fNumVerts);
    fMultColor.setSize(fNumVerts);
    fAddColor.setSize(fNumVerts);

    unsigned char* cp = fVertexData.getData();
    for (size_t i=0; i<fNumVerts; i++) {
        *(float*)cp = verts[i].fPosition.X; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Z; cp += sizeof(float);

        *(float*)cp = verts[i].fNormal.X; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Z; cp += sizeof(float);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            *(float*)cp = verts[i].fUVs[j].X; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Y; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Z; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        for (int j=0; j<weightCount; j++) {
            *(float*)cp = verts[i].fWeights[j];
            cp += sizeof(float);
        }
        if (fFormat & kSkinIndices) {
            *(int*)cp = verts[i].fIndices;
            cp += sizeof(int);
        }

        fDiffuseRGBA[i] = verts[i].fColor;
        fSpecularRGBA[i] = verts[i].fSpecularColor;
        fMultColor[i] = verts[i].fMultColor;
        fAddColor[i] = verts[i].fAddColor;
    }
}
