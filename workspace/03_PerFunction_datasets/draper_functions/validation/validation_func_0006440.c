nresults_for_project(PROJECT* p) {
    int n=0;
    for (unsigned int i=0; i<results.size(); i++) {
        if (results[i]->project == p) n++;
    }
    return n;
}
