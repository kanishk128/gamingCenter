#include<iostream>
#include<map>
#include<list>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
#include<ctime>
using namespace std;
#define nV 9
#define N 9

//Whole game map
class neighbour
{
public:
string name;
int distance;

neighbour(string name,int distance)
{
this->name=name;
this->distance=distance;
}
};
class graph{
public:
map<string,list<neighbour>> neighbourMap;
void addEdge(string u,string v,int w)
{

neighbourMap[u].push_back(neighbour(v,w));
neighbourMap[v].push_back(neighbour(u,w));
}
void print()
{
for(auto x:neighbourMap)
{
list<neighbour> neighbourList=x.second;
cout<<x.first<<": ";
for(auto y:neighbourList)
{
cout<<y.name<<" "<<y.distance<<";";
}
cout<<endl<<endl;

}
}
};
void floydWarshall(vector<vector<long long int>>& nums)
{
for(int k=0;k<9;k++)
{
for(int i=0;i<9;i++)
{
for(int j=0;j<9;j++)
{
if(nums[i][k]+nums[k][j]<nums[i][j])
{
nums[i][j]=nums[i][k]+nums[k][j];
}
}
}
}

// for(int i=0;i<9;i++)
// {
// 	for(int j=0;j<9;j++)
// 		cout<<nums[i][j]<<" ";
// 	cout<<endl;
// }
}

//Snakes & Ladders

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void shortestPath(int s, int dest, int path[]);
};

// Constructor
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// Add edge to the graph
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

// Find shortest path using Dijkstra's algorithm
void Graph::shortestPath(int s, int dest, int path[])
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(V, INT_MAX);
    pq.push(make_pair(0, s));
    dist[s] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto v : adj[u])
        {
            if (dist[v] > dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                path[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest path
    int curr = dest;
    while (curr != -1)
    {
        cout << curr << " " << "<-";
        curr = path[curr];
    }
    cout << "Start" << endl;

}


//Sudoku
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
bool isValid(int grid[N][N], int row, int col, int num) {
    // Check if the same number already exists in the row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }
    // Check if the same number already exists in the column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }
    // Check if the same number already exists in the 3x3 box
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int i = boxRow; i < boxRow + 3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }
    // If none of the above conditions are met, the number is valid
    return true;
}
// Create a vector to store the empty cells in the grid
bool solveSudoku(int grid[N][N]) {
    // Find the next empty cell
    int row, col;
    bool foundEmptyCell = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                foundEmptyCell = true;
                break;
            }
        }
        if (foundEmptyCell) {
            break;
        }
    }

    // If there are no more empty cells, the puzzle is solved
    if (!foundEmptyCell) {
        return true;
    }

    // Try filling the empty cell with each possible number
    for (int num = 1; num <= N; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }

    // If none of the numbers worked, backtrack
    return false;
}

void playSudoku(int grid[N][N]){
cout << "Initial Sudoku grid:" << endl;
printGrid(grid);
bool solved = solveSudoku(grid);
if (solved) {
cout << "Solved Sudoku grid:" << endl;
printGrid(grid);
}else{
cout << "Unable to solve Sudoku grid" << endl;
}
}
void playSL(){
// Initialize game board with ladders and snakes
    int board[101];
    for (int i = 1; i <= 100; i++) {
        board[i] = i;
    }
    board[4] = 14;
    board[9] = 31;
    board[17] = 7;
    board[20] = 38;
    board[28] = 84;
    board[40] = 59;
    board[51] = 67;
    board[54] = 34;
    board[62] = 19;
    board[63] = 81;
    board[64] = 60;
    board[71] = 91;
    board[87] = 24;
    board[93] = 73;
    board[95] = 75;
    board[99] = 78;

    // Create graph
    Graph g(101);
    for (int u = 1; u <= 100; u++) {
        for (int dice = 1; dice <= 6; dice++) {
            int v = board[u + dice];
            if (v <= 100) {
                g.addEdge(u, v);
            }
        }
    }

   cout<< "You are currently at position 0" << endl << "Enter '0' to roll your dice!!" << endl ;
    int dice_roll = 1;
    do {
        cin >> dice_roll;
        if (dice_roll != 0) {
            cout << "Oops! Please enter 0 to roll your dice!" << endl;
        }
    } while (dice_roll != 0);
    
    // Random Dice number generator
    srand(time(nullptr));
    int dice_value = (rand() % 6) + 1;
    
    cout << "The number which appeared on your dice was " << dice_value << ". You are currently at position " << dice_value << endl;
    cout << "Your shortest path to victory is:" << endl;
    // Find shortest path from start to end
    int path[101];
    for (int i = 0; i <= 100; i++) {
        path[i] = -1;
    }

    g.shortestPath(dice_value, 100, path);
 
}

void mainProj(graph g,vector<vector<long long>> wMatrix,string src,int energy)
{
g.print();

cout<<"You have "<<energy<<" energy points!!"<<endl;
cout<<"Energy can be recharged at :"<<endl;
cout<<"Recharge Center: 50 Energy points"<<endl;
cout<<"Cafe: 25 Energy points"<<endl;

vector<string> searching{"Home","Cafe","Gaming_Center1","Shopping_Complex","Recharge_Center","Cinema","Food_Court","Gaming_Center2","Parking"};
int pathDist=0;
cout<<endl<<"You are at "<<src<<" !!";
cout<<endl<<"Where do you want to go?";
fflush(stdin);
string dest;
cin>>dest;
while(find(searching.begin(),searching.end(),dest)==searching.end()){
cout<<endl<<"Wrong input!! Enter again:";
cin>>dest;
}
cout<<"Enter your path:";
string place;
string prev=src;
cin>>place;
while(place!=dest)
{
while(find(searching.begin(),searching.end(),place)==searching.end()){
cout<<endl<<"Wrong input!! Enter again:";
cin>>place;
}
// path.push_back(place);
list<neighbour> neighbourList=g.neighbourMap[place];
for(auto x:neighbourList)
{
if(x.name==prev)
{
pathDist+=x.distance;
break;
}
}
prev=place;
cin>>place;
}

//calculating path distance
list<neighbour> neighbourList=g.neighbourMap[place];
for(auto x:neighbourList)
{
if(x.name==prev)
{
pathDist+=x.distance;
break;
}
}
//GAMES INITIALIZATION
int grid[N][N] = {
{0, 0, 3, 0, 2, 0, 6, 0, 0},
{9, 0, 0, 3, 0, 5, 0, 0, 1},
{0, 0, 1, 8, 0, 6, 4, 0, 0},
{0, 0, 8, 1, 0, 2, 9, 0, 0},
{7, 0, 0, 0, 0, 0, 0, 0, 8},
{0, 0, 6, 7, 0, 8, 2, 0, 0},
{0, 0, 2, 6, 0, 9, 5, 0, 0},
{8, 0, 0, 2, 0, 3, 0, 0, 9},
{0, 0, 5, 0, 1, 0, 3, 0, 0}
};
int index; //dest's index
int ind; //src's index
//finding where is place in vector of string and storing in the
//variable index
for(int i=0; i<searching.size(); i++){
    if(searching[i] == dest){
        index = i;
    }
    if(searching[i]==src){
    	ind=i;
    }
}
int energyCons=0;
if(pathDist==wMatrix[ind][index])
{
energyCons=pathDist/10;
}
else
{
energyCons=2*(pathDist/10);
}
if(energyCons>energy)
{
cout<<"You have exhausted your energy!!!";
return;
}
energy-=energyCons;
cout<<"Your path's Distance is: "<<pathDist;
cout<<endl<<"Shortest distance from "<<src<<"to "<<place<<" is: "<<wMatrix[ind][index]<<endl;
if(dest == "Gaming_Center1"||dest=="Gaming_Center2")
{
     	char input;
    cout<<"What you want to play?"<<endl;
    cout<<"Sudoku Or Snake and Ladder"<<endl;
    cout<<"press a for Sudoku and b for Snake and Ladder"<<endl;
   	cin>>input;
   	if(input == 'a')
   	{
       playSudoku(grid);
   	}
   	else if(input=='b')
   	{
   		playSL();
   	}
   	src=dest;
   	mainProj(g,wMatrix,src,energy);
}
else if(dest=="Cafe")
{
energy+=25;
src="Cafe";
mainProj(g,wMatrix,src,energy);
}
else if(dest=="Recharge_Center")
{
energy+=50;
src="Recharge Center";
mainProj(g,wMatrix,src,energy);
}
else if(dest=="Parking"||dest=="Home")
{
cout<<"Thank you for playing!!";
return;
}
else
{
src=dest;
mainProj(g,wMatrix,src,energy);
}
}

int main()
{
    //FOR SUDOKU N=9;
graph g;
//temp3->cafe
//temp1->parking
//temp2->SC shopping complex
g.addEdge("Gaming_Center1","Shopping_Complex",10);
g.addEdge("Gaming_Center1","Cafe",12);
g.addEdge("Shopping_Complex","Recharge_Center",18);
g.addEdge("Cinema","Recharge_Center",7);
g.addEdge("Cinema","Food_Court",23);
g.addEdge("Food_Court","Home",34);
g.addEdge("Food_Court","Gaming_Center2",30);
g.addEdge("Home","Cafe",41);
g.addEdge("Parking","Cinema",25);
g.addEdge("Parking","Cafe",21);
int max=INT_MAX;
vector<vector<long long>> wMatrix{{0,41,max,max,max,max,34,max,max},
{41,0,12,max,max,max,max,max,21},
{max,12,0,10,max,max,max,max,max},
{max,max,10,0,18,max,max,max,max},
{max,max,max,18,0,7,max,max,max},
{max,max,max,max,7,0,23,max,25},
{34,max,max,max,max,23,0,30,max},
{max,max,max,max,max,max,30,0,max},
{max,21,max,max,max,25,max,max,0}};
floydWarshall(wMatrix);
mainProj(g,wMatrix,"Home",100);
return 0;
}
