save()
{
  if(readOnly()) {
    debug("WavPack::File::save() -- File is read only.");
    return false;
  }


  if(ID3v1Tag()) {
    if(d->hasID3v1) {
      seek(d->ID3v1Location);
      writeBlock(ID3v1Tag()->render());
    }
    else {
      seek(0, End);
      d->ID3v1Location = tell();
      writeBlock(ID3v1Tag()->render());
      d->hasID3v1 = true;
    }
  }
  else {
    if(d->hasID3v1) {
      removeBlock(d->ID3v1Location, 128);
      d->hasID3v1 = false;
      if(d->hasAPE) {
        if(d->APELocation > d->ID3v1Location)
          d->APELocation -= 128;
      }
    }
  }


  if(APETag()) {
    if(d->hasAPE)
      insert(APETag()->render(), d->APELocation, d->APESize);
    else {
      if(d->hasID3v1)  {
        insert(APETag()->render(), d->ID3v1Location, 0);
        d->APESize = APETag()->footer()->completeTagSize();
        d->hasAPE = true;
        d->APELocation = d->ID3v1Location;
        d->ID3v1Location += d->APESize;
      }
      else {
        seek(0, End);
        d->APELocation = tell();
        writeBlock(APETag()->render());
        d->APESize = APETag()->footer()->completeTagSize();
        d->hasAPE = true;
      }
    }
  }
  else {
    if(d->hasAPE) {
      removeBlock(d->APELocation, d->APESize);
      d->hasAPE = false;
      if(d->hasID3v1) {
        if(d->ID3v1Location > d->APELocation) {
          d->ID3v1Location -= d->APESize;
        }
      }
    }
  }

   return true;
}
