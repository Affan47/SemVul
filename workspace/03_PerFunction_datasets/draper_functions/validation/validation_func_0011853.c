nextValue()
{
  if(this->cur >= this->block_items)
  {
    this->getSample(this->block + 1);
    return pair_type(this->val, this->sample.first);
  }

  this->cur++;
  if(this->run > 0)
  {
    this->val++;
    this->run--;
  }
  else
  {
    this->val += this->buffer.readNibbleCode();
    this->run = this->buffer.readNibbleCode() - 1;
  }

  return pair_type(this->val, this->sample.first + this->cur);
}
