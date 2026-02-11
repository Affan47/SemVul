dijkstra_init(Node* vs, vector<Edge>& es, double* eweights) {
    for(unsigned i=0;i<es.size();i++) {
        unsigned u=es[i].first, v=es[i].second;
        vs[u].neighbours.push_back(&vs[v]);
        vs[u].nweights.push_back(eweights[i]);
        vs[v].neighbours.push_back(&vs[u]);
        vs[v].nweights.push_back(eweights[i]);
    }
}
