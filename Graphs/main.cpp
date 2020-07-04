#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<bits/stdc++.h>
#include <vector>

using namespace std;
int N;
int G[20][20], dist[20], inSet[20], q[20], parent[20],t[20][20], Totaltime=0 ,M;
int flag =0;


int arr[100][100];

void part1()
{
    int m,k,u,v,i,j,f,s,ver,edg;

    printf("Please enter number of vertices:\n");
    scanf("%d",&ver);

    printf("Please enter number of edges:\n");
    scanf("%d",&edg);

    printf("Please enter edges in form of(u v):\n");

    for(i = 0 ; i < edg ; i++)
    {
        scanf("%d %d",&u,&v);
        arr[u][v] = 1;
        arr[v][u] = 1;
    }

    printf("Please enter starting vertex:\n");
    scanf("%d",&m);

    printf("Please enter value k:\n");
    scanf("%d",&k);



    vector <int> values;
    vector <bool> visited(ver+1,false);
    queue <pair <int,int> >Q;

    Q.push({m,0});
    visited[m] = true;

    while(!Q.empty())
    {
        f = Q.front().first;
        s = Q.front().second;

        Q.pop();

        visited[f] = true;

        if(s == k)
            values.push_back(f);

        for(i=0 ; i < edg ; i++)
        {
            if(arr[f][i] == 1 && !visited[i])
            {
                Q.push({i,s+1});
                visited[i] = true;
            }
        }
    }
    printf("\nNumber of paths:%d ",values.size());
    printf("\nThere are %d people with %d connections away starting from %d \n\n",values.size(),k,m);


}


bool isCell_Valid(std::vector<std::vector<int> > const&maze,int x,int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0)
    {
        return true;                            // then the cell is empty
    }
    else
    {
        return false;
    }                          // else it contains 1
}


bool solve_Maze(std::vector<std::vector<int> > const&maze,int x,int y,std::vector<std::vector<int> > &sol)
{
    if (x == N-1 && y==N-1 && maze[x][y]==0)    // check if the runner reached the end or not
    {
        sol[x][y] = {0};
        return true;
    }
    else
    {
        if(isCell_Valid(maze,x,y)==true)        // checks wither the current cell contain 0 or 1
        {
            sol[x][y] = {0};             // mark the location and add to the solution

        if(solve_Maze(maze,x+1,y,sol)==true)   // first move forward
        {
            return true;
        }
        if(solve_Maze(maze,x,y+1,sol)==true)    // if forward is not available move downwards
        {
            return true;
        }
        sol[x][y] = {1};              // if the runner reached a dead end then back-track and remove the mark
        return false;
    }
    return false;
}
}




void print_solution(std::vector<std::vector<int> > &sol){

   printf("Two Dimensional array elements:\n");
   for(int x=0; x<N; x++) {

      for(int y=0;y<N;y++) {

        if(sol[x][y]== 0){

         printf("(%d,%d)\t",x,y);
         }
    }
   }
}

bool isMaze_Valid(std::vector<std::vector<int> > const&maze)
{
    vector<vector<int> > sol( N , vector<int> (N,1));
printf("\nConstructed maze:\n");
    for(int x=0; x<N; x++) {
    printf("\n");
      for(int y=0;y<N;y++) {

         printf("%d",maze[x][y]);

    }
   }
    if (solve_Maze(maze, 0, 0, sol) == false) {
        printf("\nSolution doesn't exist");
        return false;
    }

    print_solution(sol);
    return true;
}

void part2(){



printf("ENTER N :\t");
    scanf("%d",&N);
    vector<vector<int> > maze( N , vector<int> (N));
    int x,y;
    printf("Enter Values for the maze:\n");
    for(x=0; x<N; x++)
    {
        for(y=0; y<N; y++)
        {
            printf("Enter value for cell[%d][%d]:", x, y);
            scanf("%d",&maze[x][y]);
        }
    }

    isMaze_Valid(maze);



}


void printPath( int i)
{



    if (parent[i] == - 1)
        return;


    if(flag >0)
        Totaltime+=1;
    Totaltime+= t[parent[i]][i];

    flag++;
    printPath(parent[i]);


    printf("->%d ", i);
}


int printSolution( int V,int d,int S)
{

    printf("The route with minimum cost is ");
    for (int i = 1; i <= V; i++)
    {
        if (i==d)
        {
            printf("%d ",S);
            printPath(i );
            printf("\ntotal time is %d hours",Totaltime);
            if (flag>1)
            printf("\ntotal cost is %d",dist[i]+M*Totaltime);
            else
                printf("\ntotal cost is %d",dist[i]);

        }
    }
}


int Q( int V )
{
    int sum = 0, i ;
    for( i = 1 ; i <= V ; i++ )
        sum += q[i] ;
    return sum ;
}


int extractMin( int V )
{
    int i, idx, min = 1000 ;
    for ( i = 1 ; i <= V ; i++ )
    {
        if ( dist[i] <= min && inSet[i] == 0 )
            min = dist[i], idx = i ;
    }
    q[idx] = 0 ;
    return idx ;
}


void dijkstra ( int S, int V,int d)
{

    int u, i, check_empty = Q(V);

    while( check_empty >0 )
    {
        u = extractMin(V) ;

        inSet[u] = 1 ;

        for( i = 1 ; i <= V ; i++ )
        {
            if( G[u][i] > 0 )
            {
                if( dist[u] + G[u][i] < dist[i] )
                {
                    dist[i] = dist[u] + G[u][i], parent[i] = u;

                }
            }

        }

        Totaltime=t[u][i];

        check_empty = Q(V);

    }

    printSolution(V, d,S);

}

void part3()
{

    int V, i, j, S,E,d,time;
    int source,dest,cost;

    printf ( "please enter amount M:  " ) ;
    scanf ( "%d", &M ) ;

    printf ( "please enter number of cities:  " ) ;
    scanf ( "%d", &V ) ;

    for(i = 1; i <=V ; i++)
    {
        for( j = 1 ; j <= V ; j++ )
        {
            G[i][j] = 0;
            t[i][j] = 0;
        }
    }
    printf("please enter number of routes:");
    scanf("%d",&E);
    for ( i = 1 ; i <=E ; i++ )
    {

        scanf( "%d %d %d %d", &source,&dest,&time,&cost);
        G[source][dest] = cost;
        t[source][dest] =time;

    }
    for ( i = 1 ; i <= V ; i++ )
        dist[i] = 1000, inSet[i] = 0, q[i] = 1, parent[i] = -1 ;

    printf ( "Enter the source city: " ) ;
    scanf ( "%d", &S ) ;
    printf ( "Enter the destination city: " ) ;
    scanf ( "%d", &d) ;

    dist[ S ] = 0 ;
    dijkstra ( S, V,d) ;


}


int main()
{

   int selection;
           do
                {
                    printf("\nEnter(1) for part1 solution\n");
                    printf("Enter(2) for part2 solution \n");
                    printf("Enter(3) for part3 solution\n");
                    printf("Enter(4) for Exit\n");

                    printf("Enter your selection:");

                    scanf("%d",&selection);

                    if(selection==1)
                    {
                        part1();

                    }
                    else if(selection==2){

                        part2();
                    }

                    else if(selection==3)
                    {
                       part3();


                    }
                     else if(selection==4)
                    {

                          exit(0);

                    }


                    else{
                            printf("\nWrong Choice. Please try again.\n\n");
                            main();
                            }

             }while(selection<5);


    return 0;

}
