#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<regex>

using namespace std;

int main()
{
    const int buffer_size = 256;
    const int divider = 100;

    char buffer[buffer_size];
    string input;
    smatch lineMatch;
    regex lineRegex ("([LR])(\\d{1,3})\\n?");
    char direction;
    int step;
    int value = 50;
    int result1 = 0;
    int result2 = 0;
   
    memset(buffer, 0, buffer_size);

    while(fgets(buffer, buffer_size, stdin) != NULL)
    {
        string token(buffer);
        if(!regex_match(token, lineMatch, lineRegex)) { continue; }
       
        direction = string(lineMatch[1])[0];
        step = stoi(lineMatch[2]);
       
        switch(direction)
        {
            case 'L':
                if (value == 0) { value += divider; }
                value -= step;
                while(value < 0)
                {
                    value += divider;
                    result2++;
                }
                if(value == 0) { result2++; }
                break;
            case 'R':
                value += step;
                while(value >= divider)
                {
                    value -= divider;
                    result2++;
                }
                break;
            default:
                break;
        }
       
        if(value == 0)
        {
            result1++;
        }
    }
   
    printf("%i\n", result1);
    printf("%i\n", result2);

    return 0;
}