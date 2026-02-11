interrupt()
{
  lock();


  if(myPlayingSomething)
    myLastItem.interrupt();
  myPlayingSomething = false;
  unlock();
}
