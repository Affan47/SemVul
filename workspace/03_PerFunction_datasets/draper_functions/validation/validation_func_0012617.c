appendMatrix(int number, int type,
                              const CoinBigIndex * starts, const int * index,
                              const double * element, int numberOther)
{
     int numberErrors = 0;

     if (type == 0) {

          if (matrix_->isColOrdered() && numberOther > matrix_->getNumCols())
               matrix_->setDimensions(-1, numberOther);
          if (!matrix_->isColOrdered() || numberOther >= 0 || matrix_->getExtraGap()) {
               numberErrors = matrix_->appendRows(number, starts, index, element, numberOther);
          } else {

               matrix_->appendMinorFast(number, starts, index, element);


          }
     } else {

          if (!matrix_->isColOrdered() && numberOther > matrix_->getNumRows())
               matrix_->setDimensions(numberOther, -1);
	  if (element)
	    numberErrors = matrix_->appendCols(number, starts, index, element, numberOther);
	  else
	    matrix_->setDimensions(-1,matrix_->getNumCols()+number);
     }
     clearCopies();
     numberActiveColumns_ = matrix_->getNumCols();
     return numberErrors;
}
