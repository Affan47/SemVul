initializeWeights()
{
     int numberRows = model_->numberRows();
     int numberColumns = model_->numberColumns();
     int number = numberRows + numberColumns;
     int iSequence;
     if (mode_ != 1) {


          if (!reference_) {
               int nWords = (number + 31) >> 5;
               reference_ = new unsigned int[nWords];
               CoinZeroN(reference_, nWords);
          }

          for (iSequence = 0; iSequence < number; iSequence++) {
               weights_[iSequence] = 1.0;
               if (model_->getStatus(iSequence) == ClpSimplex::basic) {
                    setReference(iSequence, false);
               } else {
                    setReference(iSequence, true);
               }
          }
     } else {
          CoinIndexedVector * temp = new CoinIndexedVector();
          temp->reserve(numberRows +
                        model_->factorization()->maximumPivots());
          double * array = alternateWeights_->denseVector();
          int * which = alternateWeights_->getIndices();

          for (iSequence = 0; iSequence < number; iSequence++) {
               weights_[iSequence] = 1.0 + ADD_ONE;
               if (model_->getStatus(iSequence) != ClpSimplex::basic &&
                         model_->getStatus(iSequence) != ClpSimplex::isFixed) {
                    model_->unpack(alternateWeights_, iSequence);
                    double value = ADD_ONE;
                    model_->factorization()->updateColumn(temp, alternateWeights_);
                    int number = alternateWeights_->getNumElements();
                    int j;
                    for (j = 0; j < number; j++) {
                         int iRow = which[j];
                         value += array[iRow] * array[iRow];
                         array[iRow] = 0.0;
                    }
                    alternateWeights_->setNumElements(0);
                    weights_[iSequence] = value;
               }
          }
          delete temp;
     }
}
