ReduceDataDispersion( AllData& alldata ) {

    bool error= false;

    assert( 1 < alldata.numRanks );


    StartMeasurement( alldata, 1, true, "reduce data dispersion" );

    VerbosePrint( alldata, 1, true, "reducing data dispersion\n" );


    uint32_t num_rounds= Logi( alldata.numRanks ) -1;
    uint32_t round_no= 0;
    uint32_t round= 1;

    while ( round < alldata.numRanks ) {

        round_no++;

        if ( 1 == alldata.params.verbose_level ) {

            VerbosePrint( alldata, 1, true, " round %u / %u\n",
                         round_no, num_rounds );
        }

        uint32_t peer= alldata.myRank ^ round;


        if ( peer >= alldata.numRanks ) {

            round= round << 1;
            continue;
        }


        uint32_t sizes[12];
        char* buffer;

        if ( alldata.myRank < peer ) {

            MPI_Status status;

            MPI_Recv( sizes, 12, MPI_UNSIGNED, peer, 4, MPI_COMM_WORLD,
                     &status );


            buffer= prepare_worker_data( alldata, sizes );

            VerbosePrint( alldata, 2, false,
                         "round %u / %u: receiving %u bytes from rank %u\n",
                         round_no, num_rounds, sizes[0], peer );

            MPI_Recv( buffer, sizes[0], MPI_PACKED, peer, 5, MPI_COMM_WORLD,
                     &status );

            unpack_worker_data( alldata, sizes );

        } else {


            alldata.functionMapGlobal.clear();
            if(alldata.params.dispersion.mode == DISPERSION_MODE_PERCALLPATH)
                alldata.functionCallpathMapGlobal.clear();

            buffer= pack_worker_data( alldata, sizes );


            VerbosePrint( alldata, 2, false,
                         "round %u / %u: sending %u bytes to rank %u\n",
                         round_no, num_rounds, sizes[0], peer );

            MPI_Send( sizes, 12, MPI_UNSIGNED, peer, 4, MPI_COMM_WORLD );

            MPI_Send( buffer, sizes[0], MPI_PACKED, peer, 5,
                     MPI_COMM_WORLD );


            break;
        }

        round= round << 1;
    }
    alldata.freePackBuffer();


    if ( !error ) {


        StopMeasurement( alldata, true, "reduce data dispersion" );
    }

    return !error;
}
