/**
 @file WeightedGraph.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file for a
 weighted graph.

 @version Original Code 1.00 (11/20/2017) - Ethan M. Park
 
 @date Wednesday, November 29, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of WeightedGraph.h, which
 contains the definition for the class WeightedGraph. This class serves
 to create a weighted graph. Multiple helper function are used to help
 with indexing as well as seting and accessing members.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

// Precompiler Directives //////////////////////////////////////////
//
///// NONE
//
// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include "WeightedGraph.h"
using namespace std;
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
///// NONE
//
// Free Function Prototypes ///////////////////////////////////////
//
///// NONE
//
// Class/Data Structure Member Implementation //////////////////////
//
/** @brief Member Function: WeightedGraph::WeightedGraph(int maxNumber)
 * A default constructor for the WeightedGraph class.
 *
 * This function will set WeightedGraph members to inital values
 *
 * @param maxNumber the max row and colomn size for the array
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the weighted graph with default values.
 *
 */
WeightedGraph::WeightedGraph(int maxNumber)
{
  maxSize = maxNumber;
  size = 0;
  vertexList = new Vertex[maxNumber];
  adjMatrix = new int[maxNumber*maxNumber];
  pathMatrix = new int[maxNumber*maxNumber];
  for(int i=0; i<maxSize; i++)
  {
    for(int j=0; j<maxSize; j++)
    {
      setEdge(i,j,INFINITE_EDGE_WT);
    }
  }
}
/** @brief Member Function:WeightedGraph::WeightedGraph(const WeightedGraph& other)
 * A copy constructor for the WeightedGraph class. 
 *
 * This function will be used to initialize the a weighted
 * graph with the values of another graph.
 *
 * @param other Contains the source graph that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the graph with the values of another graph.
 *
 */
WeightedGraph::WeightedGraph(const WeightedGraph& other)
{
  maxSize = other.size;
  size = other.size;
  vertexList = new Vertex[maxSize];
  adjMatrix = new int[maxSize*maxSize];
  pathMatrix = new int[maxSize*maxSize];
  for(int i=0; i<maxSize; i++)
  {
    vertexList[i] = other.vertexList[i];
    for(int j=0; j<maxSize; j++)
    {
      adjMatrix[(i*maxSize)+j] = other.adjMatrix[(i*maxSize)+j];
    }
  }
}
/** @brief Member Function: WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
 * An overloaded assignment operator for the WeightedGraph class.
 *
 * This function will be used to initialize the a weighted
 * graph with the values of another grpah.
 *
 * @param other Contains the source graph that will be copied
 * @return WeightedGraph& Returns the address of the this graph
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the graph with the values of another graph.
 *
 */
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
{
  if(this != &other)
  {
    delete [] vertexList;
    delete [] adjMatrix;
    delete [] pathMatrix;
    maxSize = other.size;
    size = other.size;
    vertexList = new Vertex[maxSize];
    adjMatrix = new int[maxSize*maxSize];
    pathMatrix = new int[maxSize*maxSize];
    for(int i=0; i<maxSize; i++)
    {
      vertexList[i] = other.vertexList[i];
      for(int j=0; j<maxSize; j++)
      {
        adjMatrix[(i*maxSize)+j] = other.adjMatrix[(i*maxSize)+j];
      }
    }
  }
  return *this;
}
/** @brief Member Function: WeightedGraph::~WeightedGraph()
 * The destructor for the WeightedGraph class.
 *
 * This function will be used to deallocate dynamic
 * memory in the weighted graph, deleting all its
 * dynamic arrays.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Deletes the data of the graph.
 *
 */
WeightedGraph::~WeightedGraph()
{
  delete [] vertexList;
  delete [] adjMatrix;
  delete [] pathMatrix;
}
/** @brief Member Function: void WeightedGraph::insertVertex(const Vertex& newVertex) throw(logic_error)
 * Inserts a vertex into the weighted graph
 *
 * This function will take a vertex and inserts
 * the vertex, initializing a new vertex with no
 * edges or replacing a vertex if it has the
 * same label. Uses the helper function setEdge().
 *  
 * @param &newVertex Vertex item that will be inserted into the graph.
 * @return NONE
 * 
 * @exception Graph cannot be full.
 * 
 * @pre Graph is does not contain vetex.
 * @post Vertex is inserted into graph.
 *
 */
void WeightedGraph::insertVertex(const Vertex& newVertex) throw(logic_error)
{
  for(int i=0; i<size; i++)
  {
    if(vertexList[i].getLabel() == newVertex.getLabel())
    {
      vertexList[i] = newVertex;
      for(int j=0; j<size; j++)
      {
        setEdge(i, j, INFINITE_EDGE_WT);
      }
      return;
    }
  }
  if(isFull())
  {
    throw(logic_error("insertVertex() graph full"));
  }
  else
  {
    vertexList[size] = newVertex;
    for(int i=0; i<=size; i++)
    {
      setEdge(size, i, INFINITE_EDGE_WT);
    }
  }
  size++;
}
/** @brief Member Function: void WeightedGraph::insertEdge(const string& v1, const string& v2, int wt) throw(logic_error)
 * Inserts an edge into the weighted graph
 *
 * This function will take 2 vertices and inserts
 * an edge between the 2 vertices. Uses the helper
 * function setEdge()
 *  
 * @param &v1 First vertex.
 * @param &v2 Second vertex.
 * @param wt Weight of the edge.
 * @return NONE
 * 
 * @exception Vertices must exist in graph.
 * 
 * @pre Heap is does not contain edge.
 * @post Edge is inserted between 2 given vertices.
 *
 */
 void WeightedGraph::insertEdge(const string& v1, const string& v2, int wt) throw(logic_error)
{
  int a = getIndex(v1);
  int b = getIndex(v2);
  if(a>=size || b>=size)
  {
    throw(logic_error("insertEdge() no matching vertex"));
  }
  else
  {
    setEdge(a,b,wt);
  }
}
/** @brief Member Function: bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData) const
 * Retrieves a vertex from the weighted graph
 *
 * This function will retrieve a vertex
 * if it exists in the graph.
 *  
 * @param &v Label of vertex.
 * @param &vData Will contain the vertex if found.
 * @return Returns a boolean, true if it finds the vertex and false if not.
 * 
 * @exception NONE
 * 
 * @pre Given a graph.
 * @post Will get vertex from graph if it exists.
 *
 */
bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData) const
{
  for(int i=0; i<size; i++)
  {
    if(vertexList[i].getLabel() == v)
    {
      vData = vertexList[i];
      return true;
    }
  }
  return false;
}
/** @brief Member Function: bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt) const throw (logic_error)
 * Retrieves the weight of an edge from the weighted graph
 *
 * This function will retrieve the
 * weight of an edge between to given
 * vertices if it exists in the graph.
 * Uses the helper function getEdge().
 *  
 * @param &v1 First vertex.
 * @param &v2 Second vertex.
 * @param &wt Will contain the weight of the edge.
 * @return Returns a boolean, true if it finds the edge and false if not.
 * 
 * @exception Vertices must exist in graph.
 * 
 * @pre Given a graph.
 * @post Will get the weight of an edge from graph if it exists.
 *
 */
bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt) const throw (logic_error)
{
  int a = getIndex(v1);
  int b = getIndex(v2);
  if(a>=size || b>=size)
  {
    throw(logic_error("getEdgeWeight() no matching vertex"));
  }
  else if(getEdge(a,b) != INFINITE_EDGE_WT)
  {
    wt = getEdge(a, b);
    return true;
  }
  return false;
}
/** @brief Member Function: void WeightedGraph::removeVertex(const string& v) throw (logic_error)
 * Removes a vertex from the weighted graph
 *
 * This function will remove a vertex from the
 * weigted graph and will rearrange the graph
 * to account for the removed vertex.
 *  
 * @param &v Vertex to be removed.
 * @return NONE
 * 
 * @exception Graph cannot be empty.
 * 
 * @pre Graph contains vertex.
 * @post Vertex is removed from graph.
 *
 */
void WeightedGraph::removeVertex(const string& v) throw (logic_error)
{
  int remove = getIndex(v);
  if(remove>=size)
  {
    throw(logic_error("removeVertex() no matching vertex"));
  }
  else
  {
    //all edges greater than or equal to remove's edge have their vertices shifted 1 up
    //shifting rows
    for(int col=remove; col<size-1; col++) //iterates through remove's edges and all edges after
    {
      for(int row=0; row<size; row++)//iterates through all vertices
      {
        adjMatrix[row*maxSize+col] = adjMatrix[row*maxSize+(col+1)]; //shifts verticies 1 up
      }
    }
    //all edges from vertices that are greater or equal to remove's vertex are shifted 1 up
    //shifting cols
    for(int col=0; col<size-1; col++)  //iterates through all edges 
    {
      for(int row=remove; row<size; row++)  //iterates through remove and all vertices after remove
      {
        adjMatrix[row*maxSize+col] = adjMatrix[(row+1)*maxSize+col]; //shifts edges 1 up
      }
    }
    //shift vertexes up 1 (overwrite removed vertex)
    //for(int i=0; i<size; i++)
   // {
      for(int j=remove; j<size; j++)
      {
        vertexList[j] = vertexList[j+1];
      }
    //}
    size--;
  }
}
/** @brief Member Function: void WeightedGraph::removeEdge(const string& v1, const string& v2) throw (logic_error)
 * Removes a vertex from the weighted graph
 *
 * This function will remove an edge from the
 * weigted graph. Uses the helper function 
 * setEdge().
 *  
 * @param &v1 First vertex.
 * @param &v2 Second vertex.
 * @return NONE
 * 
 * @exception Vertices must exist in graph.
 * 
 * @pre Graph edge vertex.
 * @post Edge is removed from graph.
 *
 */
 void WeightedGraph::removeEdge(const string& v1, const string& v2) throw (logic_error)
{
  int a = getIndex(v1);
  int b = getIndex(v2);
  if(a>=size || b>=size)
  {
    throw(logic_error("removeEdge() no matching vertex"));
  }
  else
  {
    setEdge(a,b,INFINITE_EDGE_WT);
  }
}
/** @brief Member Function: void WeightedGraph::clear()
 * Clears data from graph.
 *
 * This function will clear the weighted graph, by setting
 * its size to zero.
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a weighted graph.
 * @post clears the graphs data.
 *
 */
void WeightedGraph::clear()
{
  size = 0;
}
/** @brief Member Function: bool WeightedGraph::isEmpty() const
 * Checks if the graph is empty
 *
 * This function checks if the graph is empty by
 * checking if the size is zero.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the graph is empty, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a max heap.
 * @post Returns true if the graph is empty and false if not.
 *
 */
bool WeightedGraph::isEmpty() const
{
  if(size==0)
  {
    return true;
  }
  return false;
}
/** @brief Member Function: bool WeightedGraph::isFull() const
 * Checks if the graph is full
 *
 * This function checks if the graph is full by
 * checking if the size equals max size.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the graph is full, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a max heap.
 * @post Returns true if the graph is full and false if not.
 *
 */
bool WeightedGraph::isFull() const
{
  if(size==maxSize)
  {
    return true;
  }
  return false;
}

//--------------------------------------------------------------------
/** @brief Member Function: void WeightedGraph:: showStructure () const
 * Shows the graph structure.
 *
 * This function shows the structure of
 * a graph.
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Outputs the structure of the graph.
 *
 */
void WeightedGraph:: showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
//#if LAB12_TEST2
		<< '\t'<< vertexList[row].getColor()
//#endif
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}
/** @brief Member Function: void WeightedGraph::showShortestPaths()
 * Shows the shortest paths between all
 * vertices in the graph
 *
 * This function creates a path matrix,
 * fills it with the shortest paths between
 * all vertices in the graph, and outputs
 * the matrix. Uses the helper functions
 * setPath(), getPath(), and getEdge()
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Outputs the shortest paths between vertices.
 *
 */
void WeightedGraph::showShortestPaths()
{
  for(int i=0; i<size; ++i)
  {
    for(int j=0; j<size; ++j)
    {
      setPath(i,j,getEdge(i,j));
    }
    setPath(i,i,0);
  }

  for(int m=0; m<size; ++m)
  {
    for(int j=0; j<size; ++j)
    {
      for(int k=0; k<size; ++k)
      {
        if(getPath(j,m) != INFINITE_EDGE_WT 
        && getPath(m,k) != INFINITE_EDGE_WT
        && getPath(j,m) + getPath(m,k) < getPath(j,k))
        {
          setPath(j,k,(getPath(j,m) + getPath(m,k)));
        }
      }
    }
  }
  
  cout << endl << "Path matrix : " << endl << '\t';
  for(int col = 0; col < size; col++)
  cout << col << '\t';
  cout << endl;

  for(int row = 0; row < size; row++)
  {
    cout << row << '\t';
    for(int col = 0; col < size; col++)
    {
      int wt = getPath(row,col);
      if(wt == INFINITE_EDGE_WT)
      {
        cout << "- \t";
      }
      else
      {
        cout << wt << '\t';
      }
    }
    cout << endl;
  }
}
/** @brief Member Function: bool WeightedGraph::hasProperColoring() const
 * Checks if the graph has proper coloring.
 *
 * This function checks if the graph has
 * proper coloring by checking if adgacent
 * objects have the same color.
 *
 * @param NONE
 * @return Returns a boolean, true if the graph has proper coloring and false if not.
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Returns true if the graph has proper coloring and false if not.
 *
 */
bool WeightedGraph::hasProperColoring() const
{
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      if(vertexList[i].getColor()==vertexList[j].getColor()
      && getEdge(i,j)!=INFINITE_EDGE_WT
      && i!=j)
      {
        return false;
      }
    }
  }
  return true;
}
/** @brief Member Function: bool WeightedGraph::areAllEven() const
 * Checks if vertices are of even degree.
 *
 * This function checks if vertices are
 * of even degree. Uses the helper function
 * getEdge().
 *
 * @param NONE
 * @return Returns a boolean, true vertices are of even degree and false if not.
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Returns true vertices are of even degree and false if not.
 *
 */
bool WeightedGraph::areAllEven() const
{
  int count=0;
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      if(getEdge(i,j)!=INFINITE_EDGE_WT)
      {
        count++;
      }
    }
    if(count%2==1)
    {
      return false;
    }
    count=0;
  }
  return true;
}

//--------------------------------------------------------------------
//
//  Facilitator functions
//
/** @brief Member Function: int WeightedGraph::getIndex ( const string& v ) const
 * Returns the index of a given label.
 *
 * This returns the index of a given label
 * or size if the label is not found.
 *
 * @note This function was provided by Dr. Harris.
 *
 * @param &v Label of vertex
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Returns the index of a vertex corressponding to a give label if it exists.
 *
 */
int WeightedGraph::getIndex ( const string& v ) const
// Returns the adjacency matrix index for vertex v. Returns size if
// the vertex does not exist.

{
    int j;  // Loop counter

    for ( j = 0 ;
          j < size  &&  vertexList[j].getLabel() != v;
          j++ );
    return j;
}
/** @brief Member Function: int WeightedGraph::getEdge(int row, int col) const
 * Returns an edge of the graph.
 *
 * This returns the edge of the
 * graph corresonding to the given
 * row and column.
 *
 * @param row Row of the edge
 * @param col Column of the edge
 * @return Returns the edge
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Returns an edge from the graph.
 *
 */
int WeightedGraph::getEdge(int row, int col) const
{
  return adjMatrix[(row * maxSize) + col];
}
/** @brief Member Function: void WeightedGraph::setEdge(int row, int col, int wt)
 * Sets an edge of the graph.
 *
 * This sets the edge of the
 * graph corresonding to the given
 * row and column to the given weight.
 *
 * @param row Row of the edge
 * @param col Column of the edge
 * @param wt weight of the edge
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Sets an edge in the graph.
 *
 */
void WeightedGraph::setEdge(int row, int col, int wt)
{
  adjMatrix[(row * maxSize) + col] = wt;
  adjMatrix[(col * maxSize) + row] = wt;
}
/** @brief Member Function: int WeightedGraph::getPath(int row, int col) const
 * Returns a path of the graph.
 *
 * This returns a path of the
 * graph corresonding to the given
 * row and column.
 *
 * @param row Row of the path
 * @param col Column of the path
 * @return Returns the path
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Returns a path from the graph.
 *
 */
int WeightedGraph::getPath(int row, int col) const
{
  return pathMatrix[(row * maxSize) + col];
}
/** @brief Member Function: void WeightedGraph::setPath(int row, int col, int wt)
 * Sets a path of the graph.
 *
 * This sets the edge of the
 * graph corresonding to the given
 * row and column to the given weight.
 *
 * @param row Row of the path
 * @param col Column of the path
 * @param wt weight of the path
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a graph.
 * @post Sets a path in the graph.
 *
 */
void WeightedGraph::setPath(int row, int col, int wt)
{
  pathMatrix[(row * maxSize) + col] = wt;
  pathMatrix[(col * maxSize) + row] = wt;
}




