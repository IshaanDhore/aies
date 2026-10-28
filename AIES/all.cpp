AIES LCA — ALL CODE IN ONE FILE
================================
Study/reference compilation. Each section is a separate program or language; this combined file is not meant to be compiled as one source file.
The face-detection section includes the OpenCV C++ reference version. The original submitted face-detection program was Python.


==============================================================================
FILE: 00_Water_Jug.cpp
==============================================================================

#include <iostream>
#include <algorithm>
using namespace std;

class jug
{
    int j3=0,j4=0;

public:
    void fill3()
    {
        j3=3;
    }

    void fill4()
    {
        j4=4;
    }

    void empty3()
    {
        j3=0;
    }

    void empty4()
    {
        j4=0;
    }

    void pour34()
    {
        int emp=4-j4;
        int pour=min(emp,j3);
        j3-=pour;
        j4+=pour;
    }

    void pour43()
    {
        int emp=3-j3;
        int pour=min(emp,j4);
        j4-=pour;
        j3+=pour;
    }

    void display()
    {
        cout<<"3L Jug: "<<j3<<"  4L Jug: "<<j4<<endl;
    }
};

int main()
{
    jug j;

    j.fill3();
    j.display();
    j.pour34();
    j.display();
    j.fill3();
    j.pour34();
    j.display();
    j.empty4();
    j.pour34();
    j.display();

    return 0;
}


==============================================================================
FILE: 01_Astar_8_Puzzle.cpp
==============================================================================

#include <iostream>
#include <algorithm>
using namespace std;

int goal[3][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

void print(int a[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

int h(int a[3][3])
{
    int count=0;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(a[i][j]!=0 && a[i][j]!=goal[i][j])
                count++;

    return count;
}

int main()
{
    int puzzle[3][3];

    cout<<"Enter initial puzzle (0 for blank):\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>puzzle[i][j];

    cout<<"\nInitial State:\n";
    print(puzzle);

    int steps=0;

    while(h(puzzle)!=0 && steps<50)
    {
        int x=-1,y=-1;

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(puzzle[i][j]==0)
                {
                    x=i;
                    y=j;
                }

        int bestH=100,bx=-1,by=-1;
        int dx[]={-1,1,0,0};
        int dy[]={0,0,-1,1};

        for(int d=0;d<4;d++)
        {
            int nx=x+dx[d],ny=y+dy[d];

            if(nx<0 || nx>2 || ny<0 || ny>2)
                continue;

            swap(puzzle[x][y],puzzle[nx][ny]);
            int hv=h(puzzle);
            swap(puzzle[x][y],puzzle[nx][ny]);

            if(hv<bestH)
            {
                bestH=hv;
                bx=nx;
                by=ny;
            }
        }

        if(bx==-1)
            break;

        swap(puzzle[x][y],puzzle[bx][by]);
        steps++;

        cout<<"Next State:\n";
        print(puzzle);
    }

    if(h(puzzle)==0)
        cout<<"Goal State Reached!\n";
    else
        cout<<"Stopped after "<<steps<<" steps (stuck or step limit reached).\n";

    return 0;
}


==============================================================================
FILE: 01b_Astar_Heuristics_Original_Submission.cpp
==============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;

class A_star
{
private:
    int a[3][3];
    int b[3][3];

public:
    A_star()
    {
        cout<<"Enter the initial state of the puzzle (3x3 matrix):\n";
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>a[i][j];

        cout<<"Enter the goal state of the puzzle (3x3 matrix):\n";
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>b[i][j];
    }

    int misplaced_tiles()
    {
        int count=0;

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(a[i][j]!=b[i][j])
                    count++;

        return count;
    }

    int manhattan_distance()
    {
        int distance=0;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(a[i][j]!=b[i][j])
                {
                    int x=0,y=0;

                    for(int m=0;m<3;m++)
                        for(int n=0;n<3;n++)
                            if(b[m][n]==a[i][j])
                            {
                                x=m;
                                y=n;
                            }

                    distance+=abs(i-x)+abs(j-y);
                }
            }
        }

        return distance;
    }

    void initialize()
    {
        int h1=misplaced_tiles();
        int h2=manhattan_distance();

        cout<<"\nInitial State:\n";
        print();

        cout<<"\nMisplaced Tiles = "<<h1<<endl;
        cout<<"Manhattan Distance = "<<h2<<endl;
        cout<<"f(n) using Misplaced Tiles = "<<h1<<endl;
        cout<<"f(n) using Manhattan Distance = "<<h2<<endl;
    }

    void print()
    {
        cout<<"\nPuzzle:\n";
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }

        cout<<"\nGoal State:\n";
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                cout<<b[i][j]<<" ";
            cout<<endl;
        }
    }
};

int main()
{
    A_star astar;
    astar.initialize();
    astar.print();
    return 0;
}


==============================================================================
FILE: 02_TSP_Hill_Climbing.cpp
==============================================================================

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


==============================================================================
FILE: 02b_TSP_Exhaustive_Permutation_Original_Submission.cpp
==============================================================================

#include <iostream>
using namespace std;

int graph[10][10];
int tour[10];
int visited[10];
int n;
int minDist=999999;
int bestTour[10];

void calcDist()
{
    int dist=0;

    for(int i=0;i<n-1;i++)
        dist+=graph[tour[i]][tour[i+1]];

    dist+=graph[tour[n-1]][tour[0]];

    if(dist<minDist)
    {
        minDist=dist;
        for(int i=0;i<n;i++)
            bestTour[i]=tour[i];
    }
}

void generateTour(int pos)
{
    if(pos==n)
    {
        calcDist();
        return;
    }

    for(int i=0;i<n;i++)
    {
        if(visited[i]==0)
        {
            visited[i]=1;
            tour[pos]=i;
            generateTour(pos+1);
            visited[i]=0;
        }
    }
}

int main()
{
    cout<<"Enter the number of nodes in the graph: "<<endl;
    cin>>n;

    if(n<2 || n>10)
    {
        cout<<"Enter nodes between 2 and 10.\n";
        return 0;
    }

    cout<<"Enter the weights of the graph in matrix format: "<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>graph[i][j];

    generateTour(0);

    cout<<"Best path: "<<endl;
    for(int i=0;i<n;i++)
        cout<<bestTour[i]+1<<" ";
    cout<<bestTour[0]+1<<endl;

    cout<<"Minimum Distance: "<<minDist;
    return 0;
}


==============================================================================
FILE: 03_CSP_SEND_MORE_MONEY_Backtracking.cpp
==============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

int main()
{
    string str1="SEND";
    string str2="MORE";
    string str3="MONEY";

    vector<char> unique_chars;
    string all=str1+str2+str3;

    for(char ch:all)
    {
        bool found=false;

        for(char x:unique_chars)
        {
            if(x==ch)
            {
                found=true;
                break;
            }
        }

        if(!found)
            unique_chars.push_back(ch);
    }

    int n=unique_chars.size();
    int digit[26]={};
    bool used[10]={};

    function<bool(int)> solve = [&](int pos)
    {
        if(pos==n)
        {
            int SEND=digit['S'-'A']*1000+
                     digit['E'-'A']*100+
                     digit['N'-'A']*10+
                     digit['D'-'A'];

            int MORE=digit['M'-'A']*1000+
                     digit['O'-'A']*100+
                     digit['R'-'A']*10+
                     digit['E'-'A'];

            int MONEY=digit['M'-'A']*10000+
                      digit['O'-'A']*1000+
                      digit['N'-'A']*100+
                      digit['E'-'A']*10+
                      digit['Y'-'A'];

            return SEND+MORE==MONEY;
        }

        char ch=unique_chars[pos];

        for(int d=0;d<=9;d++)
        {
            if(d==0 && (ch=='S' || ch=='M'))
                continue;

            if(used[d])
                continue;

            digit[ch-'A']=d;
            used[d]=true;

            if(solve(pos+1))
                return true;

            used[d]=false;
        }

        return false;
    };

    if(solve(0))
    {
        cout<<"Solution:\n";

        for(char ch:unique_chars)
            cout<<ch<<" = "<<digit[ch-'A']<<endl;

        cout<<"\n";
        cout<<" "<<digit['S'-'A']<<digit['E'-'A']
            <<digit['N'-'A']<<digit['D'-'A']<<endl;
        cout<<"+ "<<digit['M'-'A']<<digit['O'-'A']
            <<digit['R'-'A']<<digit['E'-'A']<<endl;
        cout<<"------"<<endl;
        cout<<digit['M'-'A']<<digit['O'-'A']
            <<digit['N'-'A']<<digit['E'-'A']
            <<digit['Y'-'A']<<endl;
    }

    return 0;
}


==============================================================================
FILE: 03b_CSP_SEND_MORE_MONEY_Nested_Loops_Original_Submission.cpp
==============================================================================

#include <iostream>
using namespace std;

int main()
{
    for(int S=1;S<=9;S++)
    for(int E=0;E<=9;E++)
    for(int N=0;N<=9;N++)
    for(int D=0;D<=9;D++)
    for(int M=1;M<=9;M++)
    for(int O=0;O<=9;O++)
    for(int R=0;R<=9;R++)
    for(int Y=0;Y<=9;Y++)
    {
        if(S==E || S==N || S==D || S==M || S==O || S==R || S==Y)
            continue;

        if(E==N || E==D || E==M || E==O || E==R || E==Y)
            continue;

        if(N==D || N==M || N==O || N==R || N==Y)
            continue;

        if(D==M || D==O || D==R || D==Y)
            continue;

        if(M==O || M==R || M==Y || O==R || O==Y || R==Y)
            continue;

        int SEND=1000*S+100*E+10*N+D;
        int MORE=1000*M+100*O+10*R+E;
        int MONEY=10000*M+1000*O+100*N+10*E+Y;

        if(SEND+MORE==MONEY)
        {
            cout<<"S = "<<S<<endl;
            cout<<"E = "<<E<<endl;
            cout<<"N = "<<N<<endl;
            cout<<"D = "<<D<<endl;
            cout<<"M = "<<M<<endl;
            cout<<"O = "<<O<<endl;
            cout<<"R = "<<R<<endl;
            cout<<"Y = "<<Y<<endl;

            cout<<"\nSEND = "<<SEND;
            cout<<"\nMORE = "<<MORE;
            cout<<"\nMONEY = "<<MONEY<<endl;
            return 0;
        }
    }

    return 0;
}


==============================================================================
FILE: 04_Prolog_Weather_Expert_System.cpp
==============================================================================

#include <iostream>
using namespace std;

int main()
{
    int temperature,humidity;
    string precipitation;

    cout<<"Enter temperature: ";
    cin>>temperature;
    cout<<"Enter humidity: ";
    cin>>humidity;
    cout<<"Enter precipitation (none/rain): ";
    cin>>precipitation;

    if(precipitation=="rain")
    {
        cout<<"Weather is rainy.\n";
        cout<<"Take an umbrella and wear waterproof boots.\n";
    }
    else if(temperature>=25 && precipitation=="none")
    {
        cout<<"Weather is sunny.\n";
        cout<<"Wear sunglasses and sunscreen. Great day for a walk!\n";
    }
    else if(temperature<10)
    {
        cout<<"Weather is cold.\n";
        cout<<"Wear a heavy jacket and a beanie.\n";
    }
    else
        cout<<"No matching weather rule found.\n";

    return 0;
}


==============================================================================
FILE: 04_Weather_Expert_System.pl
==============================================================================

% Facts: Define current weather parameters
temperature(28).
humidity(45).
precipitation(none).

% Rules: Weather classification
weather(sunny) :- temperature(T), T >= 25, precipitation(none).
weather(rainy) :- precipitation(rain).
weather(cold) :- temperature(T), T < 10.

% Recommendations
recommendation(sunny, 'Wear sunglasses and sunscreen. Great day for a walk!').
recommendation(rainy, 'Take an umbrella and wear waterproof boots.').
recommendation(cold, 'Wear a heavy jacket and a beanie.').

% Main query: run forecast.
forecast :-
    weather(W),
    recommendation(W, Advice),
    format('Weather is ~w. Recommendation: ~w~n', [W, Advice]).


==============================================================================
FILE: 05_Tic_Tac_Toe_Minimax.cpp
==============================================================================

#include <iostream>
#include <algorithm>
using namespace std;

char board[3][3]={
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

void printBoard()
{
    cout<<"\n";
    cout<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
    cout<<"\n";
}

bool checkWin(char player)
{
    for(int i=0;i<3;i++)
    {
        if((board[i][0]==player && board[i][1]==player && board[i][2]==player) ||
           (board[0][i]==player && board[1][i]==player && board[2][i]==player))
            return true;
    }

    if((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
       (board[0][2]==player && board[1][1]==player && board[2][0]==player))
        return true;

    return false;
}

bool isfull()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return false;

    return true;
}

int minimax(bool isMaximizing)
{
    if(checkWin('O'))
        return 10;

    if(checkWin('X'))
        return -10;

    if(isfull())
        return 0;

    if(isMaximizing)
    {
        int bestScore=-1000;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='O';
                    int score=minimax(false);
                    board[i][j]=' ';
                    bestScore=max(score,bestScore);
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore=1000;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='X';
                    int score=minimax(true);
                    board[i][j]=' ';
                    bestScore=min(score,bestScore);
                }
            }
        }

        return bestScore;
    }
}

void bestmove()
{
    int bestScore=-1000;
    int moveRow=-1,moveCol=-1;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                int score=minimax(false);
                board[i][j]=' ';

                if(score>bestScore)
                {
                    bestScore=score;
                    moveRow=i;
                    moveCol=j;
                }
            }
        }
    }

    if(moveRow!=-1 && moveCol!=-1)
        board[moveRow][moveCol]='O';
}

int main()
{
    cout<<"Tic Tac Toe Game\n";
    cout<<"You are X, AI is O\n";
    printBoard();

    while(true)
    {
        int row,col;
        cout<<"Enter your move (row and column: 0-2): ";
        cin>>row>>col;

        if(row<0 || row>2 || col<0 || col>2 || board[row][col]!=' ')
        {
            cout<<"Invalid move. Try again.\n";
            continue;
        }

        board[row][col]='X';
        printBoard();

        if(checkWin('X'))
        {
            cout<<"You win!\n";
            break;
        }

        if(isfull())
        {
            cout<<"It's a draw!\n";
            break;
        }

        bestmove();
        printBoard();

        if(checkWin('O'))
        {
            cout<<"AI wins!\n";
            break;
        }

        if(isfull())
        {
            cout<<"It's a draw!\n";
            break;
        }
    }

    return 0;
}


==============================================================================
FILE: 06_Face_Detection_OpenCV_Python_Reference.cpp.txt
==============================================================================

import cv2
import matplotlib.pyplot as plt

imagePath = r"C:\Users\HP\OneDrive\Desktop\Rohit's python\face_detection\people.jpg"
cascadePath = r"C:\Users\HP\OneDrive\Desktop\Rohit's python\face_detection\haarcascade_frontalface_default.xml"

# Create the Haar Cascade
face_cascade = cv2.CascadeClassifier(cascadePath)

# Read the image
image = cv2.imread(imagePath)

# Check files
if face_cascade.empty():
    print("ERROR: Haar Cascade file could not be loaded.")
    exit()

if image is None:
    print("ERROR: Image could not be loaded.")
    exit()

# Convert image to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Detect faces
faces = face_cascade.detectMultiScale(
    gray,
    scaleFactor=1.1,
    minNeighbors=10,
    minSize=(40, 40)
)

print("Found {0} faces!".format(len(faces)))

# Draw rectangles
for (x, y, w, h) in faces:
    cv2.rectangle(
        image,
        (x, y),
        (x + w, y + h),
        (0, 255, 0),
        2
    )

# Convert BGR to RGB
RGB_img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

plt.imshow(RGB_img)
plt.axis("off")
plt.show()



==============================================================================
FILE: COVID_CHATBOT_MINI_EXPERT_SYSTEM.py
==============================================================================

def covid3():
    print("how can i help you ")
    covid_sym = ["cough", "headache", "cold", "fever", "breath issue", "taste loss"]
    sym_l = []
    n = int(input("how many symptoms you want: "))
    for i in range(n):
        sym = input("Enter the symptoms: ").lower().strip()
        if sym in covid_sym:
            sym_l.append(sym)
    if len(sym_l) > 0:
        print("symptoms found:", sym_l)
        print("These symptoms can have many causes. Please seek advice from a qualified healthcare professional if you are concerned.")
    else:
        print("No listed symptoms were matched. This does not rule out illness.")


def covid():
    s = input("Enter the symptom: ")
    sym = s.lower().strip()
    if sym == "cough" or sym == "headache":
        print("Symptom matched. This is not a diagnosis.")
    elif sym == "cold" or sym == "fever":
        print("Symptom matched. This is not a diagnosis.")
    elif sym == "breath issue" or sym == "taste loss":
        print("Symptom matched. This is not a diagnosis.")
    elif sym == "muscle aches" or sym == "fatigue":
        print("Symptom matched. This is not a diagnosis.")
    else:
        print("I could not match that symptom.")

if __name__ == "__main__":
    choice = input("Enter 1 for one symptom or 2 for multiple symptoms: ").strip()
    if choice == "1":
        covid()
    elif choice == "2":
        covid3()
    else:
        print("Invalid choice")