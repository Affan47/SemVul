PrintFasta(const BamAlignment& a) {


    m_out << "> " << a.Name << endl;


    string sequence = a.QueryBases;
    if ( a.IsReverseStrand() )
        Utilities::ReverseComplement(sequence);


    if ( sequence.length() <= FASTA_LINE_MAX )
        m_out << sequence << endl;


    else {

        size_t position = 0;
        size_t seqLength = sequence.length();


        while ( position < (seqLength - FASTA_LINE_MAX) ) {
            m_out << sequence.substr(position, FASTA_LINE_MAX) << endl;
            position += FASTA_LINE_MAX;
        }


        m_out << sequence.substr(position) << endl;
    }
}
