LineBufferTask::~LineBufferTask ()
{


    _lineBuffer->post ();
}
