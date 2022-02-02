#include<stdio.h>
#include<stdlib.h>
// a graph doesn't contain an odd cycle if and only if it's bipartite, so we check if the graph is bipartite, if its then it doesn't have an odd cycle

//a graph is bipartite if and only if it can be colored with 2 colors minimum we can also express this ass  if and only if it contains no odd cycles

// BFS Algorithm:
//if there is 2 adjacent vertecies with the same color, then it can't be bipartite
//to implement BFS, we need to use queue
//BFS, visist all the nodes adjecnet to the current node and color them with an opposite color if there weren't visited before,
//if they are visited then we check the color, if its same then it can't be bipartite, else we check the other nodes

//Time efficiency: O(|V| + |E|), v = number of nodes, E= numbers of edges, since we are using BFS

int size = 0;
typedef struct queue
{
    int  *arr;
    int head, tail, qsize;
} queue;
void push(queue *q, int item)
{
    if(q->qsize < size)   
    {
        ++q->qsize;
        q->arr[q->tail++] = item;   
    }          

}
int pop(queue *q)
{
    if(q->qsize)
    {
        --q->qsize;
        return q->arr[q->head++];
    }       
        
}
int isEmpty(queue *q)
{
    return q->qsize == 0;
}

int bipartite_BFS(int** graph, int v, int *color)
{
    queue *q = (queue*) malloc(sizeof(queue));// creating queue and initializing it
    q->qsize = 0, q->head= 0, q->tail = 0;
    q->arr = (int*) malloc(size * size * sizeof(int));// allocating memeory
    color[v] = 1;    
    push(q, v);

    while(!isEmpty(q))//this will loop will be  O(|E|) if we used adjacent list, it also can be |V^2| if we used matrix representation
    {
        v = pop(q);
        for(int i =0; i < size; ++i)//
        {
            if(graph[v][i] && color[i] == -1)// if a this adj node isn't visited
            {
                push(q, i); //push it to the queue
                color[i] = 1 - color[v]; // coloring opposite to its adj vertix
            }
            else if(graph[v][i] && color[v] == color[i])// if a this adj node is visited // and has they have the same color
                return 0;//its not bipartite
        }
    }
    return 1;// if there is no 2 adj vertecies with  the same color then its bipartite
}

int disconnected_Bipartite_BFS(int** graph)//this  can be used if the graph is disconnected
{
    int *color = (int*) malloc(size*sizeof(int));
    int i =0;
    //initializing the color array so every node is not visited
    for(i = 0; i < size;++i) //O(n)
        color[i] = -1;

    for(i = 0; i < size;++i) //O(n) // if the graph is disconnected it will check for each connected component
        if(color[i] == -1)
            if(bipartite_BFS(graph, 0, color))
                return 1;
    return 0;    
}


int main()
{
    int i = 0, j = 0;
    scanf("%d", &size); //size

    int **gMatrix = (int**) malloc (size *sizeof(int*)); // matrix memory allocation
    for(i =0; i < size; ++i)
        gMatrix[i] = (int*) malloc (size *sizeof(int));

    for(i = 0; i < size; ++i) //scanning input
        for(j = 0; j < size; ++j)
            scanf("%d", &gMatrix[i][j]);

    if(!disconnected_Bipartite_BFS(gMatrix)) // if it's not bipartite then it means that it has an odd cycle.
        printf("true\n");
    else
        printf("false\n");   
}