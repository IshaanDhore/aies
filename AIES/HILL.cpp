#include <iostream>
using namespace std;

int cost[10][10];
int path[10];
int n;

int calcCost()
{
    int total=0;

    for(int i=0;i<n-1;i++)
        total+=cost[path[i]][path[i+1]];

    total+=cost[path[n-1]][path[0]];
    return total;
}

int main()
{
    cout<<"Enter number of cities: ";
    cin>>n;

    if(n<2 || n>10)
    {
        cout<<"Enter cities between 2 and 10.\n";
        return 0;
    }

    cout<<"Enter cost matrix:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>cost[i][j];

    for(int i=0;i<n;i++)
        path[i]=i;

    int bestCost=calcCost();
    bool improved=true;

    while(improved)
    {
        improved=false;

        for(int i=1;i<n-1;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                swap(path[i],path[j]);
                int newCost=calcCost();

                if(newCost<bestCost)
                {
                    bestCost=newCost;
                    improved=true;
                }
                else
                    swap(path[i],path[j]);
            }
        }
    }

    cout<<"\nBest Path: ";
    for(int i=0;i<n;i++)
        cout<<path[i]+1<<" ";
    cout<<path[0]+1;

    cout<<"\nMinimum Cost: "<<bestCost<<endl;
    return 0;
}

// g++ file.cpp -o file
// .\file