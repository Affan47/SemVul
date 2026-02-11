GetAverageColor(int c[3])
    {
      if(this->AverageCount)
        {
        c[0] = static_cast<int>(this->AverageColor[0] / this->AverageCount);
        c[1] = static_cast<int>(this->AverageColor[1] / this->AverageCount);
        c[2] = static_cast<int>(this->AverageColor[2] / this->AverageCount);
        }
    }
