enum class Phase
{
    start,
    update,
    end,
    idle
};

std::ostream &operator<<(std::ostream &stream, const Phase phase)
{
    switch (phase)
    {
    case Phase::start:
        stream << "START";
        break;
    case Phase::update:
        stream << "UPDATE";
        break;
    case Phase::end:
        stream << "END";
        break;
    case Phase::idle:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}