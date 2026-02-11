display() const
{
    mycerr << "Below is the list of your configuration entries:\n";
    mycerr << "\n";
    for (auto& p : impl_)
    {
        mycerr << "    " << setw(16) << std::left << p.first << p.second << "\n";
    }
}
