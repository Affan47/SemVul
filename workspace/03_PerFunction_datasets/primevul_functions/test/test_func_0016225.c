void DL_Dxf::addLeader(DL_CreationInterface* creationInterface) {

    DL_LeaderData le(

        getIntValue(71, 1),

        getIntValue(72, 0),

        getIntValue(73, 3),

        getIntValue(74, 1),

        getIntValue(75, 0),

        getRealValue(40, 1.0),

        getRealValue(41, 1.0),

        getIntValue(76, 0)
    );
    creationInterface->addLeader(le);

    for (int i=0; i<maxLeaderVertices; i++) {
        DL_LeaderVertexData d(leaderVertices[i*3],
                              leaderVertices[i*3+1],
                              leaderVertices[i*3+2]);

        creationInterface->addLeaderVertex(d);
    }
    creationInterface->endEntity();
}
