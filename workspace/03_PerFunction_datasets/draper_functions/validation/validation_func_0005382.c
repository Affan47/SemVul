calculateME(vector<int> h) {

  complex answer(0,0);
  for (int mu = 0; mu <= 3; mu++) {
    answer +=
	(u[1][h[pMap[1]]] * gamma[mu] * (1 - gamma[5]) * u[0][h[pMap[0]]])
	* gamma[4](mu,mu) * u[2][0](mu);
  }
  return answer;

}
