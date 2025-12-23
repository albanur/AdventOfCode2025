#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cctype>
#include<regex>
#include<vector>
#include<set>

using namespace std;

struct Range
{
    int64_t from;
    int64_t to;

    Range(int64_t from = 0, int64_t to = 0) : from(from), to(to) { }

    Range(const Range& rng) : from(rng.from), to(rng.to) { }

    size_t Hash() const
    {
        return ((size_t)from << 8) ^ (size_t)to;
    }
   
    bool IsInRange(int64_t value) const
    {
        return from <= value && value <= to;
    }
   
    bool Overlaps(const Range& rng)
    {
        return IsInRange(rng.from) || IsInRange(rng.to)
            || rng.IsInRange(from) || rng.IsInRange(to);
    }
   
    Range Combine(const Range& rng)
    {
        return Range(
            from < rng.from ? from : rng.from,
            to > rng.to ? to : rng.to);
    }
   
    bool IsValid()
    {
        return from <= to;
    }
   
    int64_t Count()
    {
        return to - from + 1LL;
    }
};

bool operator < (const Range& r1, const Range& r2)
{
    return (r1.from < r2.from) || (r1.from == r2.from && r1.to < r2.to);
}

bool operator == (const Range& r1, const Range& r2)
{
    return r1.from == r2.from && r1.to == r2.to;
}

struct RangeHash {
   size_t operator()(const Range &point) const
   {
        return point.Hash();
   }
};

class RangeCollection
{
private:
    set<Range> ranges;
   
public:
    RangeCollection() { }
   
    void Add(const Range& rng)
    {
        Range toBeAdded(rng);
        Range r = FindOverlappingRange(toBeAdded);
       
        while(r.IsValid())
        {
            ranges.erase(r);
            toBeAdded = toBeAdded.Combine(r);
            r = FindOverlappingRange(toBeAdded);
        }
       
        if(toBeAdded.IsValid())
        {
            ranges.insert(toBeAdded);
        }
    }
   
    int64_t Count()
    {
        int64_t result = 0LL;
       
        for(auto r : ranges)
        {
            result += r.Count();
        }
       
        return result;
    }
   
private:
    Range FindOverlappingRange(const Range& rng)
    {
        for(auto r : ranges)
        {
            if(r.Overlaps(rng))
            {
                return r;
            }
        }
       
        return Range(0, -1);
    }
};

int main()
{
    const int bufferSize = 1024;
    char buffer[bufferSize];
    smatch rangeMatch;
    regex rangeRegex ("(\\d+)\\-(\\d+)\\n?");
    vector<Range> ranges;
    int result1 = 0;
    int64_t result2 = 0;
    RangeCollection rngCol;
   
    while(fgets(buffer, bufferSize, stdin) != NULL)
    {
        string range(buffer);
        if(regex_match(range, rangeMatch, rangeRegex))
        {
            int64_t from = stoll(rangeMatch[1]);
            int64_t to = stoll(rangeMatch[2]);
            ranges.push_back(Range(from, to));
            rngCol.Add(Range(from, to));
        }
        else
        {
            break;
        }
    }
   
    while(fgets(buffer, bufferSize, stdin) != NULL)
    {
        if(strlen(buffer) == 0) { continue; }
       
        int64_t value = atoll(buffer);
        for(auto rng : ranges)
        {
            if(rng.IsInRange(value))
            {
                result1++;
                break;
            }
        }
    }
   
    result2 = rngCol.Count();
   
    printf("%d\n", result1);
    printf("%lld\n", result2);

    return 0;
}