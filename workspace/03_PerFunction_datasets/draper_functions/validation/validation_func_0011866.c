removeAdj(string& from, const string& adj) {
	string cap_adj = adj;
	cap_adj[0] = toupper(cap_adj[0]);

	if (from.size() <= adj.size() || from[adj.size()] != ' ')
		return false;
	if (from[0] != adj[0] && from[0] != toupper(adj[0]))
		return false;
	if (from.compare(1, adj.size() - 1, adj, 1, adj.size() - 1))
		return false;

	from.erase(0, adj.size() + 1);
	return true;
}
