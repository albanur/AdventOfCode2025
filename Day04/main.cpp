#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cctype>
#include<vector>
#include<map>
#include<algorithm>
#include<regex>

using namespace std;

enum DirectionType : int
{
    DirectionN = 0,
    DirectionS = 1,
    DirectionW = 2,
    DirectionE = 3,
    DirectionNW = 4,
    DirectionNE = 5,
    DirectionSW = 6,
    DirectionSE = 7,

    DirectionMin = 0,
    DirectionMax = 7,
};

struct Point
{
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) { }

    Point(const Point& pt) : x(pt.x), y(pt.y) { }

    Point(const Point& pt, DirectionType direction) : x(pt.x), y(pt.y)
    {
        Move(direction);
    }

    void Move(DirectionType direction)
    {
        switch(direction)
        {
            case DirectionN:
                y--; break;
            case DirectionS:
                y++; break;
            case DirectionW:
                x--; break;
            case DirectionE:
                x++; break;
            case DirectionNW:
                x--; y--; break;
            case DirectionNE:
                x++; y--; break;
            case DirectionSW:
                x--; y++; break;
            case DirectionSE:
                x++; y++; break;
            default:
               break;
        }
    }
};

class Board
{
private:
    vector<vector<char>> board;

public:
    Board() { }

    void Read(FILE* input)
    {
        const int bufferSize = 1024;
        char buffer[bufferSize];
        memset(buffer, 0, bufferSize);

        while(fgets(buffer, bufferSize, input) != NULL)
        {
            AddLine(buffer);
        }
    }
   
    int CountRollsForForklift()
    {
        int sum = 0;
        char tile;
        Point point;
       
        for(int j = 0; j < board.size(); j++)
        {
            for(int i = 0; i < board[j].size(); i++)
            {
                point = Point(i, j);
                tile = GetTile(point);
               
                if(tile != '@') { continue; }
               
                int adjectentRolls = 0;
                for(DirectionType d = DirectionMin; d <= DirectionMax; d = (DirectionType)(d+1))
                {
                    tile = GetAdjescentTile(point, d);
                    if(tile == '@') { adjectentRolls ++; }
                }
               
                if(adjectentRolls < 4)
                {
                    sum++;
                    //printf("(%i,%i)\n", i, j);
                }
            }
        }
       
        return sum;
    }
   
    void GetRollsForForklift(vector<Point>& positions)
    {
        positions.clear();
        char tile;
        Point point;
       
        for(int j = 0; j < board.size(); j++)
        {
            for(int i = 0; i < board[j].size(); i++)
            {
                point = Point(i, j);
                tile = GetTile(point);
               
                if(tile != '@') { continue; }
               
                int adjectentRolls = 0;
                for(DirectionType d = DirectionMin; d <= DirectionMax; d = (DirectionType)(d+1))
                {
                    tile = GetAdjescentTile(point, d);
                    if(tile == '@') { adjectentRolls ++; }
                }
               
                if(adjectentRolls < 4)
                {
                    positions.push_back(point);
                }
            }
        }
    }
   
    void ClearRolls(vector<Point>& positions)
    {
        for(auto point : positions)
        {
            ClearTile(point);
        }
    }
   
    void PrintBoard()
    {
        for(int j = 0; j < board.size(); j++)
        {
            for(int i = 0; i < board[j].size(); i++)
            {
                Point point = Point(i, j);
                char tile = GetTile(point);
                printf("%c", tile);
            }
            printf("\n");
        }
    }


private:
    void AddLine(const char* line)
    {
        vector<char> row;
        const char* ptr = line;

        while(*ptr != 0)
        {
            switch(*ptr)
            {
                case '.':
                case '@':
                    row.push_back(*ptr);
                default:
                    ptr++;
            }
        }

        if(row.size() > 0)
        {
            board.push_back(row);
        }
    }

    char GetAdjescentTile(const Point& point, DirectionType direction)
    {
        Point neighbour(point);
        neighbour.Move(direction);
        return GetTile(neighbour);
    }

    bool IsOnBoard(const Point& point)
    {
        return point.y >= 0 && point.y < (int)board.size()
            && point.x >= 0 && point.x < (int)board[point.y].size();
    }

    char GetTile(const Point& point)
    {
        return IsOnBoard(point)
            ? board[point.y][point.x]
            : '.';
    }
   
    void ClearTile(const Point& point)
    {
        if(IsOnBoard(point))
        {
            board[point.y][point.x] = '.';
        }
    }
};

int main()
{
    Board board;
    int sum = 0;
    int sum2 = 0;

    board.Read(stdin);
    sum = board.CountRollsForForklift();
    printf("%i\n", sum);
   
    vector<Point> positions;
    board.GetRollsForForklift(positions);
    while(positions.size() > 0)
    {
        sum2 += positions.size();
        board.ClearRolls(positions);
        board.GetRollsForForklift(positions);
    }
    printf("%i\n", sum2);

    return 0;
}