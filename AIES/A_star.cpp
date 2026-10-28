#include <iostream>
using namespace std;


const int MAX_STATES = 20000;

struct Node
{
    int state[3][3];
    int g, h, f;
};

int heuristic(int a[3][3], int goal[3][3])
{
    int count = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(a[i][j] != 0 && a[i][j] != goal[i][j])
                count++;
    return count;
}

void copyState(int a[3][3], int b[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            b[i][j] = a[i][j];
}

void printState(int a[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

bool isSame(int a[3][3], int b[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(a[i][j] != b[i][j])
                return false;
    return true;
}

bool isVisited(Node open[], int totalNodes, int state[3][3])
{
    for(int i = 0; i < totalNodes; i++)
    {
        if(isSame(open[i].state, state))
            return true;
    }
    return false;
}

int main()
{
    Node open[MAX_STATES];
    int rear = 0;

    int goal[3][3];

    cout << "Enter Start State (0 for blank):\n";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            cin >> open[0].state[i][j];

    cout << "\nEnter Goal State:\n";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            cin >> goal[i][j];

    open[0].g = 0;
    open[0].h = heuristic(open[0].state, goal);
    open[0].f = open[0].g + open[0].h;
    rear = 1;

    int openCount = 1; 

    while(openCount > 0)
    {
        int best = -1;
        int minF = 999999;

        for(int i = 0; i < rear; i++)
        {
            if(open[i].g != -1 && open[i].f < minF)
            {
                minF = open[i].f;
                best = i;
            }
        }

        if(best == -1)
        {
            cout << "\nNo solution found or queue empty!";
            break;
        }

        Node current = open[best];
        
        open[best].g = -1; 
        openCount--;

        cout << "\n--- Step " << current.g << " (f = " << current.f << ") ---" << endl;
        printState(current.state);

        if(isSame(current.state, goal))
        {
            cout << "\nGoal Reached successfully in " << current.g << " moves!" << endl;
            break;
        }

        int x = -1, y = -1;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(current.state[i][j] == 0)
                {
                    x = i;
                    y = j;
                }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for(int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
            {
                Node child;
                copyState(current.state, child.state);
                swap(child.state[x][y], child.state[nx][ny]);
                if(!isVisited(open, rear, child.state))
                {
                    if(rear < MAX_STATES)
                    {
                        child.g = current.g + 1;
                        child.h = heuristic(child.state, goal);
                        child.f = child.g + child.h;

                        open[rear++] = child;
                        openCount++;
                    }
                    else
                    {
                        cout << "\nMemory limit reached (MAX_STATES overflow)!" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}

// g++ file.cpp -o file
// .\file