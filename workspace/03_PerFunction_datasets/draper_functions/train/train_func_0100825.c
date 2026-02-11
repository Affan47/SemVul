sendrealdata(int arrayno, int blocknumber, int blkndx,
                  int target, int tarray,
                  int tblock,int nwblock, MPI_Comm *comm, int msgtype,
                  MPI_Request *request)
{


    int i, tag;
    static double *buffer;
    MPI_Status status;
    double d;

    buffer = c_get_block_data_addr(arrayno, blocknumber, blkndx);
    if (buffer)
    {

       i = find_available_msg_buffer();
       msgbuf[i][0]=msgtype;
       msgbuf[i][1]=tarray;
       msgbuf[i][2]=tblock;
       tag = form_msg_tag() + tag_limit;
       msgbuf[i][3] = tag;
       msgbuf[i][4] = nwblock;

       MPI_Isend(buffer, nwblock, MPI_DOUBLE, target, tag, *comm, request);
       MPI_Isend(msgbuf[i], 5, MPI_INT, target, readytag, *comm, &ready_request[i]);
       nmessage_count++;
    }
    else
    {
       printf("Error: sendrealdata cannot find array, block %d %d in blkmgr.\n", arrayno, blocknumber);
       MPI_Abort(MPI_COMM_WORLD, 0);
    }
}
