runQuickSort(int list[], int lowestIndex, int highestIndex, bool applyRandom){
	if(lowestIndex >= highestIndex){
		return;
	}

	if(applyRandom){
		int pivotIndex = getRandomInteger(lowestIndex, highestIndex);
		swap(&list[lowestIndex], &list[pivotIndex]);
	}
	int pivotValue = list[lowestIndex];
	int pivotIndex = lowestIndex;

	for(int index = lowestIndex + 1; index <= highestIndex; index ++){
		if(list[index] < pivotValue){
			pivotIndex += 1;
			swap(&list[index], &list[pivotIndex]);
		}
	}
	swap(&list[lowestIndex], &list[pivotIndex]);

	runQuickSort(list, lowestIndex, pivotIndex - 1, applyRandom);
	runQuickSort(list, pivotIndex + 1, highestIndex, applyRandom);
}
