int get_pad_width(const int ngram_width) const {


    return std::min(pad_width_ < 0 ? ngram_width - 1 : pad_width_,
                    ngram_width - 1);
  }
