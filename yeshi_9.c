/*
	Graph를 다루기 위해 사용할 코드 파일이에요.

	주:
		- 여러 algorithm들을 보다 편리하게 구현할 수 있도록 작성 / 편집 순서에 따라 코드를 나열해 두었어요.
		- 작성 편의를 위해 typedef을 조금 넣어 두었어요.
*/


#include <stdio.h>
#include <stdlib.h>

/*
	Vertex 설정
*/

// TODO: 문제의 특징에 따라 각 vertex마다 어떤 값을 담을 지 파악하여 적절한 멤버 선언 적기
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

// TODO: Vertex 구조체의 구성에 따라 적절한 값을 미리 담아 두도록 구성하기
void Init_Vertex(V *vertexToInitialize)
{
	vertexToInitialize->state = V_WHITE;
	vertexToInitialize->distance = 0x7FFFFFFF;
	vertexToInitialize->idx_v_from = -1;
}


/*
	Edge 설정
*/

// TODO: 문제의 특징에 따라 각 edge마다 어떤 값을 담을 지 파악하여 구조체 형식으로 만들거나 그냥 int 형식 쓰기
//       (적어도 'edge 있음' 정도는 나타내야 하므로 int 값 하나 정도는 필요할 거예요)
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

// TODO: Edge 구성에 따라 적절한 값을 미리 담아 두도록 구성하기
void Init_Edge(E *edgeToInitialize)
{
	*edgeToInitialize = 0;
}





/*
	Graph 설정

	주:
		- Graph를 구성하는 vertex 수는 늘 고정되어 있다고 간주하고 있어요. (처음 만들 때 정함)
		- Edge 또한 추가만 하고 제거는 안 할 것이라고 간주하고 있어요.
			> 중복된 edge 추가에 대해서는 특별히 검사하지 않을 예정이에요.
		- 원본 graph가 Undirected graph일 때 edge 하나에 대한 정보는 두 개 생겨요. (포인터 형식을 써서 서로 '공유'하게 만들지 않음)
			> Vertex에 담긴 값은 종종 변경되지만, edge에 담긴 값을 변경하는 경우는 별로 없어요.
		- 모든 vertex는 0번부터 순서대로 번호를 갖는다고 간주하고 있어요.
*/

#define USE_ADJACENCY_LIST

#ifdef USE_ADJACENCY_LIST
// Adjacency list를 구성할 때만 사용할 node 구조체예요.
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
	Graph 자체에 대한 manipulation을 위한 함수들
*/

// 주어진 수만큼의 vertex를 갖는 새 graph를 만듭니다.
// (Edge는 나중에 Add_Edge() 써서 추가해야 함!)
G *New_Graph(int n_V)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// 사용이 끝난 graph를 해제합니다.
void Delete_Graph(G *g)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// Graph에 새 directed edge를 추가합니다.
// 원본 graph가 undirected graph라면 그냥 이거 두 번 호출하면 될 듯 해요.
void Add_Edge(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}


// v[from] -> v[to] edge가 존재하는지 여부를 return합니다.
int Adjacent(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// v[from] -> v[to] edge가 존재하는 모든 v[to]들의 수를 return합니다.
// 보통은 아래에 있는 Neighbors()를 호출하기 전에 적절한 메모리 칸을 잡아 두기 위해 호출될 거예요.
int Count_Neighbors(G *g, int idx_v_source)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
#else
	// Adjacency matrix
#endif
}

// v[from] -> v[to] edge가 존재하는 모든 v[to]들의 'index'를 out_idxs_v_target 값으로 특정되는 배열에 순서대로 담고, 그 수를 return합니다.
// 호출자가 위에 정의한 Count_Neighbors()를 먼저 호출해서 적절한 크기를 잡아 두거나,
// 귀찮으면 그냥 V칸짜리 하나 잡아 놓고 재활용해도 될 듯 해요(담은 횟수는 return값을 참고하면 됨).
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

	이제 이 아래에 main()을 비롯한 실제 프로그램 코드를 적으면 될 듯 해요.

	오늘 Graph 관련 함수를 잘 구비해 두면,
	당분간은 코드 위에 있는 vertex / edge 설정만 건드려 가며 문제를 풀 수 있을 거예요!

*/

int main()
{

	return 0;
}