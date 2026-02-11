Problem_2_test(){
    Chapter9 chapter9;
    vector<vector<int> > graph(4, vector<int>(4,0));
    graph[0][1]=1;
    graph[1][1]=1;
    graph[3][2]=1;
    vector<pair<int, int> > path;
    vector<pair<int, int> > correctPath;
    correctPath.push_back(make_pair(0,0));
    correctPath.push_back(make_pair(1,0));
    correctPath.push_back(make_pair(2,0));
    correctPath.push_back(make_pair(2,1));
    correctPath.push_back(make_pair(2,2));
    correctPath.push_back(make_pair(2,3));
    correctPath.push_back(make_pair(3,3));
    chapter9.Problem_2(graph, path);
    if(path.size()!=correctPath.size())
	return false;
    for(size_t i=0; i<path.size(); ++i){
	if(path[i].first!=correctPath[i].first)
	    return false;
	if(path[i].second!=correctPath[i].second)
	    return false;
    }
    return true;
}
