/*
	Graph�� �ٷ�� ���� ����� �ڵ� �����̿���.

	��:
		- ���� algorithm���� ���� ���ϰ� ������ �� �ֵ��� �ۼ� / ���� ������ ���� �ڵ带 ������ �ξ����.
		- �ۼ� ���Ǹ� ���� typedef�� ���� �־� �ξ����.
*/


#include <stdio.h>
#include <stdlib.h>

/*
	Vertex ����
*/

// TODO: ������ Ư¡�� ���� �� vertex���� � ���� ���� �� �ľ��Ͽ� ������ ��� ���� ����
#define V_WHITE 0
#define V_GRAY  1
#define V_BLACK 2

struct Vertex_t
{
	int state;
	int distance;
	int idx_v_from;
};

typedef struct Vertex_t V;

// TODO: Vertex ����ü�� ������ ���� ������ ���� �̸� ��� �ε��� �����ϱ�
void Init_Vertex(V *vertexToInitialize)
{
	vertexToInitialize->state = V_WHITE;
	vertexToInitialize->distance = 0x7FFFFFFF;
	vertexToInitialize->idx_v_from = -1;
}


/*
	Edge ����
*/

// TODO: ������ Ư¡�� ���� �� edge���� � ���� ���� �� �ľ��Ͽ� ����ü �������� ����ų� �׳� int ���� ����
//       (��� 'edge ����' ������ ��Ÿ���� �ϹǷ� int �� �ϳ� ������ �ʿ��� �ſ���)
//#define USE_STRUCTURED_EDGE

#ifdef USE_STRUCTURED_EDGE
struct Edge_t
{
	int weight;
};

typedef struct Edge_t E;
#else

typedef int E;

#endif

// TODO: Edge ������ ���� ������ ���� �̸� ��� �ε��� �����ϱ�
void Init_Edge(E *edgeToInitialize)
{
	*edgeToInitialize = 0;
}





/*
	Graph ����

	��:
		- Graph�� �����ϴ� vertex ���� �� �����Ǿ� �ִٰ� �����ϰ� �־��. (ó�� ���� �� ����)
		- Edge ���� �߰��� �ϰ� ���Ŵ� �� �� ���̶�� �����ϰ� �־��.
			> �ߺ��� edge �߰��� ���ؼ��� Ư���� �˻����� ���� �����̿���.
		- ���� graph�� Undirected graph�� �� edge �ϳ��� ���� ������ �� �� ���ܿ�. (������ ������ �Ἥ ���� '����'�ϰ� ������ ����)
			> Vertex�� ��� ���� ���� ���������, edge�� ��� ���� �����ϴ� ���� ���� �����.
		- ��� vertex�� 0������ ������� ��ȣ�� ���´ٰ� �����ϰ� �־��.
*/

#define USE_ADJACENCY_LIST

#ifdef USE_ADJACENCY_LIST
// Adjacency list�� ������ ���� ����� node ����ü����.
struct E_node_t
{
	E e;
	int idx_v_to;
	struct E_node_t *next;
};

typedef struct E_node_t E_node;
#endif

struct Graph_t
{
	int n_V;

	V *v;

#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *e;
#else
	// Adjacency matrix
	E **e;
#endif
};

typedef struct Graph_t G;



/*
	Graph ��ü�� ���� manipulation�� ���� �Լ���
*/

// �־��� ����ŭ�� vertex�� ���� �� graph�� ����ϴ�.
// (Edge�� ���߿� Add_Edge() �Ἥ �߰��ؾ� ��!)
G *New_Graph(int n_V)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// ����� ���� graph�� �����մϴ�.
void Delete_Graph(G *g)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// Graph�� �� directed edge�� �߰��մϴ�.
// ���� graph�� undirected graph��� �׳� �̰� �� �� ȣ���ϸ� �� �� �ؿ�.
void Add_Edge(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}


// v[from] -> v[to] edge�� �����ϴ��� ���θ� return�մϴ�.
int Adjacent(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� ���� return�մϴ�.
// ������ �Ʒ��� �ִ� Neighbors()�� ȣ���ϱ� ���� ������ �޸� ĭ�� ��� �α� ���� ȣ��� �ſ���.
int Count_Neighbors(G *g, int idx_v_source)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� 'index'�� out_idxs_v_target ������ Ư���Ǵ� �迭�� ������� ���, �� ���� return�մϴ�.
// ȣ���ڰ� ���� ������ Count_Neighbors()�� ���� ȣ���ؼ� ������ ũ�⸦ ��� �ΰų�,
// �������� �׳� Vĭ¥�� �ϳ� ��� ���� ��Ȱ���ص� �� �� �ؿ�(���� Ƚ���� return���� �����ϸ� ��).
int Neighbors(G *g, int idx_v_source, int *out_idxs_v_target)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}





/*
	Note.

	���� �� �Ʒ��� main()�� ����� ���� ���α׷� �ڵ带 ������ �� �� �ؿ�.

	���� Graph ���� �Լ��� �� ������ �θ�,
	��а��� �ڵ� ���� �ִ� vertex / edge ������ �ǵ�� ���� ������ Ǯ �� ���� �ſ���!

*/

int main()
{

	return 0;
}