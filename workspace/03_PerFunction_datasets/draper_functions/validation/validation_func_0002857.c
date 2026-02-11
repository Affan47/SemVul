extractMin() {
	int res = -1;
	int minKey = INT_MAX;
	for(int i = 0; i < n; i++ ) {
		if(data[i]->color == White && data[i]->key < minKey) {
			res = i;
			minKey = data[i]->key;
		}
	}
	return res;
}
