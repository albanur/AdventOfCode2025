#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

int FindHighestJoltage(vector<int>& row)
{
    int firstDigit = -1;
    int firstPos = -1;
    int secondDigit = -1;
   
    for(int i = 0; i < row.size()-1; i++)
    {
        if(row[i] > firstDigit)
        {
            firstDigit = row[i];
            firstPos = i;
        }
    }
   
    for(int i = firstPos + 1; i < row.size(); i++)
    {
        if(row[i] > secondDigit)
        {
            secondDigit = row[i];
        }
    }
   
    return firstDigit * 10 + secondDigit;
}

int64_t FindHighestJoltage2(vector<int>& row)
{
    int64_t result = 0;
    int currentDigit;
    int lastPos = -1;
   
    for(int j = 12; j > 0; j--)
    {
        currentDigit = -1;
       
        for(int i = lastPos + 1; i <= row.size()-j; i++)
        {
            if(row[i] > currentDigit)
            {
                currentDigit = row[i];
                lastPos = i;
            }
        }
       
        result = result * 10 + currentDigit;
    }
   
    return result;
}

int main()
{
    const int buffer_size = 1024;

    char buffer[buffer_size];
    int result1 = 0;
    int64_t result2 = 0;
    vector<int> row;
   
    while(fgets(buffer, buffer_size, stdin) != NULL)
    {
        row.clear();
       
        for(int i = 0; i < buffer_size; i++)
        {
            if('0' <= buffer[i] && buffer[i] <= '9')
            {
                row.push_back(buffer[i] - '0');
            }
            else
            {
                break;
            }
        }
       
        result1 += FindHighestJoltage(row);
        result2 += FindHighestJoltage2(row);
    }
   
    printf("%i\n", result1);
    printf("%lld\n", result2);

    return 0;
}
