Problem_8_test(){
    int stream[] = {5,3,8,4,2,1,7,6,9,3};
    Problem_8 problem8;
    for(size_t i=0; i<10; ++i){
	problem8.track(stream[i]);
    }
    int correctRank[]={5,3,8,4,1,0,7,6,9,3};
    for(size_t i=0; i<10; ++i){
	if(problem8.getRank(stream[i])!=correctRank[i]){
	    return false;
	}
    }
    return true;
}
