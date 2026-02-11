setMaximumSavedSolutions(int value)
{
    if (value < maximumSavedSolutions_) {
        for (int i = value; i < maximumSavedSolutions_; i++)
            delete [] savedSolutions_[i];
        maximumSavedSolutions_ = value;
        numberSavedSolutions_ = CoinMin(numberSavedSolutions_,
                                        maximumSavedSolutions_);
        if (!maximumSavedSolutions_)
            delete [] savedSolutions_;
    } else if (value > maximumSavedSolutions_) {
        double ** temp = new double * [value];
        int i;
        for ( i = 0; i < maximumSavedSolutions_; i++)
            temp[i] = savedSolutions_[i];
        for ( ; i < value; i++)
            temp[i] = NULL;
        delete [] savedSolutions_;
        maximumSavedSolutions_ = value;
        savedSolutions_ = temp;
    }
}
