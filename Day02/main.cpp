#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cctype>
#include<regex>
#include<vector>

using namespace std;

int CountDigits(int64_t number)
{
    int digits = 0;
    while(number > 0)
    {
        number /= 10;
        digits++;
    }
    return digits;
}

int64_t SkipLastDigits(int64_t number, int digits)
{
    while(digits > 0)
    {
        number /= 10;
        digits--;
    }
    return number;
}

int64_t ShiftDigitsLeft(int64_t number, int digits)
{
    while(digits > 0)
    {
        number *= 10;
        digits--;
    }
    return number;
}

int64_t CalculateInvalidNumber(int64_t number)
{
    int digits = CountDigits(number);
    if(digits % 2 == 1) { return 0LL; }
   
    digits /= 2;
    int64_t half = SkipLastDigits(number, digits);
    int64_t invalid = ShiftDigitsLeft(half, digits) + half;
    return invalid;
}

bool IsInvalidWithMultiplication(vector<int>& digits, int digitNum, int multi)
{
    for(int i = 0; i + multi < digitNum; i++)
    {
        if(digits[i] != digits[i+multi]) { return false; }
    }
   
    return true;
}

bool IsInvalid(int64_t number)
{
    vector<int> digits;
    int digitNum = 0;
   
    while(number > 0)
    {
        digits.push_back(number % 10);
        number /= 10;
        digitNum++;
    }
   
    for(int i = 1; i < digitNum; i++)
    {
        if(digitNum % i == 0)
        {
            if(IsInvalidWithMultiplication(digits, digitNum, i)) { return true; }
        }
    }
   
    return false;
}

int64_t CountInvalidNumbers1(int64_t from, int64_t to)
{
    int64_t result = 0LL;
    int digits = CountDigits(from);
    digits = (digits+1)/2;
    int64_t top = SkipLastDigits(from, digits);
   
    while(ShiftDigitsLeft(top, digits) < to)
    {
        int64_t value = CalculateInvalidNumber(ShiftDigitsLeft(top, digits));
        if(from <= value && value <= to) { result+=value; }
        top++;
    }
   
    return result;
}

int64_t CountInvalidNumbers2(int64_t from, int64_t to)
{
    int64_t result = 0LL;
   
    for(int64_t i = from; i <= to; i++)
    {
        if(IsInvalid(i))
        {
            result+=i;
        }
    }
   
    return result;
}

int main()
{
    const int bufferSize = 1024;
    char buffer[bufferSize];
    smatch rangeMatch;
    regex rangeRegex ("(\\d+)\\-(\\d+)[,\\n]?");
    int64_t rangeFrom;
    int64_t rangeTo;
    int64_t result1 = 0LL;
    int64_t result2 = 0LL;
   
    while(fgets(buffer, bufferSize, stdin) != NULL)
    {
        char* token = strtok(buffer, ",");
        while (token != NULL)
        {
            string stoken(token);
            if(regex_match(stoken, rangeMatch, rangeRegex))
            {
                rangeFrom = stoll(rangeMatch[1]);
                rangeTo = stoll(rangeMatch[2]);
                result1 += CountInvalidNumbers1(rangeFrom, rangeTo);
                result2 += CountInvalidNumbers2(rangeFrom, rangeTo);
            }
            token = strtok(NULL, ",");
        }
    }
   
    printf("%lld\n", result1);
    printf("%lld\n", result2);

    return 0;
}