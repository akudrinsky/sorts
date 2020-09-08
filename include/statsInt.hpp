class StatsInt;

namespace std {
    void swap(StatsInt& first, StatsInt& second);
}

class StatsInt {
public:
    StatsInt();
    StatsInt(int number);
    StatsInt(const StatsInt& other);
    StatsInt& operator = (const StatsInt& other);

    operator int();

    static unsigned long showCompares();
    static unsigned long showSwaps();

    static void restart();

    bool operator < (const StatsInt& other);
    bool operator == (const StatsInt& other);
    bool operator != (const StatsInt& other);
    bool operator > (const StatsInt& other);
    bool operator <= (const StatsInt& other);
    bool operator >= (const StatsInt& other);

private:
    int number;
    static unsigned long compareNum;
    static unsigned long swapNum;
    
    friend void std::swap(StatsInt& first, StatsInt& second);
};