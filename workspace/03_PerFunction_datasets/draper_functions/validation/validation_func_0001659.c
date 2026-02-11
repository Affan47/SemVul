getRowSpaceIterate ( int iRow,
                                      int extraNeeded )
{
  const int * numberInRow = numberInRow_.array();
  int number = numberInRow[iRow];
  CoinBigIndex * COIN_RESTRICT startRow = startRowU_.array();
  int * COIN_RESTRICT indexColumn = indexColumnU_.array();
  CoinBigIndex * COIN_RESTRICT convertRowToColumn = convertRowToColumnU_.array();
  CoinBigIndex space = lengthAreaU_ - startRow[maximumRowsExtra_];
  int * COIN_RESTRICT nextRow = nextRow_.array();
  int * COIN_RESTRICT lastRow = lastRow_.array();
  if ( space < extraNeeded + number + 2 ) {

    int iRow = nextRow[maximumRowsExtra_];
    CoinBigIndex put = 0;
    while ( iRow != maximumRowsExtra_ ) {

      CoinBigIndex get = startRow[iRow];
      CoinBigIndex getEnd = startRow[iRow] + numberInRow[iRow];

      startRow[iRow] = put;
      CoinBigIndex i;
      for ( i = get; i < getEnd; i++ ) {
	indexColumn[put] = indexColumn[i];
	convertRowToColumn[put] = convertRowToColumn[i];
	put++;
      }
      iRow = nextRow[iRow];
    }
    numberCompressions_++;
    startRow[maximumRowsExtra_] = put;
    space = lengthAreaU_ - put;
    if ( space < extraNeeded + number + 2 ) {


      status_ = -99;
      return false;    }
  }
  CoinBigIndex put = startRow[maximumRowsExtra_];
  int next = nextRow[iRow];
  int last = lastRow[iRow];


  nextRow[last] = next;
  lastRow[next] = last;

  last = lastRow[maximumRowsExtra_];
  nextRow[last] = iRow;
  lastRow[maximumRowsExtra_] = iRow;
  lastRow[iRow] = last;
  nextRow[iRow] = maximumRowsExtra_;

  CoinBigIndex get = startRow[iRow];

  int * indexColumnU = indexColumnU_.array();
  startRow[iRow] = put;
  while ( number ) {
    number--;
    indexColumnU[put] = indexColumnU[get];
    convertRowToColumn[put] = convertRowToColumn[get];
    put++;
    get++;
  }

  startRow[maximumRowsExtra_] = put + extraNeeded + 4;
  return true;
}
