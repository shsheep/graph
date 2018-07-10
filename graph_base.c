/*
	Graph�� �ٷ�� ���� ����� �ڵ� �����̿���.
	(9������ ���� ���� ��ҵ鿡 �ణ�� ����� ����� �ξ����)

	��:
		- ���� algorithm���� ���� ���ϰ� ������ �� �ֵ��� �ۼ� / ���� ������ ���� �ڵ带 ������ �ξ����.
		- �ۼ� ���Ǹ� ���� typedef�� ���� �־� �ξ����.

	���� �̷�:

	2018. 7. 9.
		- V *Get_V(G *g, int idx_v), E *Get_E(G *g, int idx_v_from, int idx_v_to)�� �߰��߾��.
			> �ش�Ǵ� vertex / edge�� graph�� �����ϴ� ��� �ش� object�� ���� ������ ���� return�ؿ�.
			> �ش�Ǵ� vertex / edge�� graph�� ���� ��� null ������ ���� return�ؿ�.
			> Adjacency list�� ���ٸ� Get_E()�� ���� ���� �� ���� �� �ؿ�.
			  Adjacency matrix�� �� ���� �׳� g->e[i][j] �ϸ� �� ��.
			  Get_V()�� ��ǻ� �׳� g->v[i] �ϸ� �Ǳ� �ؿ�(��Ī���� �����ϱ� ���� ����� ��).

		- G *Load_Graph(FILE *fp, int isUndirectedGraph)�� �߰��߾��.
			> ����(Ű���� ����)���� ���ڵ��� �о� �� graph�� ����� return�ϴ� �Լ�����.
			> ���� ���� �д� ������...
				~ ù ��° ����: Vertex ��
				~ �� ��° ����: Edge ��
				~ ���ķ� ���ڸ� �� ���� ���� �о� ���� edge�� ����� �߰��ؿ�.
				  isUndirectedGraph ���� nonzero�� ����� �ϳ���,
				  ���� zero�� �� idx -> �� idx ���� �ϳ��� ������.
			> ������ ���� �Է� ����� ���ݾ� �ٸ��״� �� �� �� �� ���ݾ� ������ ���� �� ��!

		- void Print_Graph(FILE *fp, G *g)�� �߰��߾��.
			> ����(�ܼ� â ����)�� �ش� graph�� ������ ������ print�ؿ�.
			  �ʱ� ������ �ܼ� ����� �뵵�� �� �� �ֵ��� ������ �ξ����.

			> ������ ���� ��� ����� �ſ� ���� �ٸ��� ��ǻ� ��� ����� main()���� ¥�� �� �� �ؿ�.

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

//#define USE_ADJACENCY_LIST

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
	int idx;
	int idx_column;

	// Graph ��ü �Ҵ�
	G *result = malloc(sizeof(G));

	// V �Ҵ�
	result->n_V = n_V;
	result->v = malloc(sizeof(V) * n_V);

	for ( idx = 0; idx < n_V; ++idx )
		Init_Vertex(&result->v[idx]);

	// E �Ҵ�
#ifdef USE_ADJACENCY_LIST
	// Adjacency list

	// �� vertex�� list�� head���� ���� �迭 �Ҵ�
	result->e = malloc(sizeof(E_node) * n_V);

	// �� head���� null �����ͷ� �ʱ�ȭ
	for ( idx = 0; idx < n_V; ++idx )
		result->e[idx].next = 0;
#else
	// Adjacency matrix

	// Matrix �Ҵ�
	// ù 4 * n_V byte�� row vector��, �������� n_V�� ¥�� column array��
	result->e = malloc(sizeof(E*) * n_V + sizeof(E) * n_V * n_V);

	for ( idx = 0; idx < n_V; ++idx )
	{
		// row pointer ����(������ �����غ����� ���������δ� �׳� ���ȣ ���� �� �� ������)
		result->e[idx] = &((E*)&result->e[n_V])[idx * n_V];

		for ( idx_column = 0; idx_column < n_V; ++idx_column )
			Init_Edge(&result->e[idx][idx_column]);
	}
#endif

	return result;
}

// ����� ���� graph�� �����մϴ�.
void Delete_Graph(G *g)
{
	// E ����
#ifdef USE_ADJACENCY_LIST
	// Adjacency list

	int idx_v;
	E_node *ptr;
	E_node *ptr_next;

	// �� list�� ����
	for ( idx_v = 0; idx_v < g->n_V; ++idx_v )
		for ( ptr = g->e[idx_v].next; ptr != 0; )
		{
			ptr_next = ptr->next;
			free(ptr);
			ptr = ptr_next;
		}

	// list �迭 ����
	free(g->e);

#else
	// Adjacency matrix

	// ��¥�� malloc()�� ������ �׳� �����ϸ� ��
	free(g->e);
#endif

	// V ����
	free(g->v);

	// Graph ����
	free(g);
}

// Graph�� �� directed edge�� �߰��մϴ�.
// ���� graph�� undirected graph��� �׳� �̰� �� �� ȣ���ϸ� �� �� �ؿ�.
void Add_Edge(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *newNode;
	E_node *ptr_nodeToAdd;

	// �� node ����� ���� ���
	newNode = malloc(sizeof(E_node));
	newNode->next = 0;
	newNode->idx_v_to = idx_v_to;
	Init_Edge(&newNode->e);

	// �̰� ���� ���� �� ���ϱ�(�ð��� �� �� �ɸ��� ������ �Է¹��� ������� �����ǵ��� �� �� �ڿ� ��� �־��)
	for ( ptr_nodeToAdd = &g->e[idx_v_from]; ptr_nodeToAdd->next != 0; ptr_nodeToAdd = ptr_nodeToAdd->next )
		;

	// �ű�� ���
	ptr_nodeToAdd->next = newNode;
#else
	// Adjacency matrix
	g->e[idx_v_from][idx_v_to] = 1;
#endif
}


// v[from] -> v[to] edge�� �����ϴ��� ���θ� return�մϴ�.
int Adjacent(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;

	for ( ptr = g->e[idx_v_from].next; ptr != 0; ptr = ptr->next )
		if ( ptr->idx_v_to == idx_v_to )
			return 1;

	return 0;
#else
	// Adjacency matrix

	return g->e[idx_v_from][idx_v_to] != 0;
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� ���� return�մϴ�.
// ������ �Ʒ��� �ִ� Neighbors()�� ȣ���ϱ� ���� ������ �޸� ĭ�� ��� �α� ���� ȣ��� �ſ���.
int Count_Neighbors(G *g, int idx_v_source)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;
	int count = 0;

	for ( ptr = g->e[idx_v_source].next; ptr != 0; ptr = ptr->next )
		++count;

	return count;
#else
	// Adjacency matrix
	int idx_v_target;
	int count = 0;

	for ( idx_v_target = 0; idx_v_target < g->n_V; ++idx_v_target )
		if ( g->e[idx_v_source][idx_v_target] != 0 )
			++count;

	return count;
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� 'index'�� out_idxs_v_target ������ Ư���Ǵ� �迭�� ������� ���, �� ���� return�մϴ�.
// ȣ���ڰ� ���� ������ Count_Neighbors()�� ���� ȣ���ؼ� ������ ũ�⸦ ��� �ΰų�,
// �������� �׳� Vĭ¥�� �ϳ� ��� ���� ��Ȱ���ص� �� �� �ؿ�(���� Ƚ���� return���� �����ϸ� ��).
int Neighbors(G *g, int idx_v_source, int *out_idxs_v_target)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;
	int count = 0;

	for ( ptr = g->e[idx_v_source].next; ptr != 0; ptr = ptr->next )
	{
		*out_idxs_v_target = ptr->idx_v_to;
		++out_idxs_v_target;
		++count;
	}

	return count;
#else
	// Adjacency matrix
	int idx_v_target;
	int count = 0;

	for ( idx_v_target = 0; idx_v_target < g->n_V; ++idx_v_target )
		if ( g->e[idx_v_source][idx_v_target] != 0 )
		{
			*out_idxs_v_target = idx_v_target;
			++out_idxs_v_target;
			++count;
		}

	return count;
#endif
}



// Graph�� �ִ� v[idx] object�� ���� ������ ���� return�մϴ�.
// ���� �ش� object�� �������� �ʴ� ��� null ������ ���� return�մϴ�.
// ��� ��� �Ʒ��� �ִ� Get_E()�� ��Ī���� ���߱� ���� ����� �����.
// �׳� g->v[idx_v] �ϸ� �Ǳ� ������ �׸� ���� ������ ���� �� �ؿ�.
V *Get_V(G *g, int idx_v)
{
	if ( idx_v < 0 || idx_v >= g->n_V )
		return 0;

	return &g->v[idx_v];
}

// Graph�� �ִ� v[from] -> v[to] edge object�� ���� ������ ���� return�մϴ�.
// ���� �ش� object�� �������� �ʴ� ��� null ������ ���� return�մϴ�.
// Adjacency list�� ���� ��� �� �Լ��� ���� �͵� ������ ���� �� �ؿ�.
// ����: Undirected graph�� ���� ��� edge���� �� ���� directed edge�� ���ֵǾ� �� �־��.
//       Edge�� ���� �ٲٰų� �� ���� �� ���� �����ؾ� �ؿ�.
E *Get_E(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;

	for ( ptr = g->e[idx_v_from].next; ptr != 0; ptr = ptr->next )
		if ( ptr->idx_v_to == idx_v_to )
			return &ptr->e;

	return 0;
#else
	// Adjacency matrix
	if ( idx_v_from < 0 || idx_v_from >= g->n_V ||
		idx_v_to < 0 || idx_v_to >= g->n_V )
		return 0;

	return &g->e[idx_v_from][idx_v_to];
#endif
}



// �־��� ����(Ű���� ����)���� ���ڵ��� �о� �� graph�� ����� return�մϴ�.
// - ���� ���� �д� ������...
//		> ù ��° ����: Vertex ��
//		> �� ��° ����: Edge ��
//		> ���ķ� ���ڸ� �� ���� ���� �о� ���� edge�� ����� �߰��մϴ�.
//		  �� �� isUndirectedGraph ���� nonzero�� ����� edge�� ���� �ϳ���,
//		  ���� zero�� �� idx -> �� idx ���� edge �ϳ��� ����ϴ�.
//
// TODO: ������ ���� �Է� ����� ���ݾ� �ٸ��״� �� �� �� �� ���ݾ� ������ ���� �� ��!
G *Load_Graph(FILE *fp, int isUndirectedGraph)
{
	int n_E;
	int input_left, input_right;
	G *g_new;

	// ù �� ���ڴ� ���� n_V, n_E
	fscanf(fp, "%d%d", &input_left, &n_E);

	g_new = New_Graph(input_left);

	while ( n_E > 0 )
	{
		// ���� ���ڵ��� ��� edge ������
		fscanf(fp, "%d%d", &input_left, &input_right);

		Add_Edge(g_new, input_left, input_right);

		if ( isUndirectedGraph != 0 )
			Add_Edge(g_new, input_right, input_left);

		n_E = n_E - 1;
	}

	return g_new;
}


// �־��� ����(�ܼ� â ����)�� �ش� graph�� ������ ������ print�ؿ�.
// �ʱ� ������ �ܼ� ����� �뵵�� �� �� �ֵ��� ������ �ξ����.
// ������ ���� ��� ����� �ſ� ���� �ٸ��� ��ǻ� ��� ����� main()���� ¥�� �� �� �ؿ�.
void Print_Graph(FILE *fp, G *g)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	int idx_from;
	E_node *ptr;

	for ( idx_from = 0; idx_from < g->n_V; ++idx_from )
	{
		fprintf(fp, "V[%d]: [", idx_from);

		if ( g->e[idx_from].next != 0 )
		{
			for ( ptr = g->e[idx_from].next; ptr != 0; ptr = ptr->next )
				fprintf(fp, "%d, ", ptr->idx_v_to);

			fprintf(fp, "\b\b]\n");
		}
		else
			fprintf(fp, "empty]\n");
	}
#else
	// Adjacency matrix
	int idx_from;
	int idx_to;
	for ( idx_from = 0; idx_from < g->n_V; ++idx_from )
	{
		fprintf(fp, "V[%d]: [", idx_from);
		for ( idx_to = 0; idx_to < g->n_V; ++idx_to )
			fprintf(fp, "%d, ", g->e[idx_from][idx_to]);
		fprintf(fp, "\b\b]\n");
    }
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
	int idx_v_from;
	int idx_v_to;
	int result;
	int *idxs_v_target;

	// ��: �Ʒ��� �� ����� �� �ϳ��� �����Ͽ� Ű���� �Ǵ� ���Ͽ��� graph ������ ������ �޾ƿ� �� �־��.
	//FILE *fp = fopen("input.txt", "r");
	FILE *fp = stdin;

	G *g = Load_Graph(fp, 0);

	idxs_v_target = malloc(sizeof(int) * g->n_V);

	printf("Graph overview:\n");
	Print_Graph(stdout, g);


	printf("Adjacent() test.\n");

	while ( 1 )
	{
		idx_v_from = -1;
		idx_v_to = -1;
		printf("Enter idx_v_from and idx_v_to | -1 -1 to quit>");
		scanf("%d%d", &idx_v_from, &idx_v_to);

		if ( idx_v_from == -1 || idx_v_to == -1 )
			break;

		result = Adjacent(g, idx_v_from, idx_v_to);

		if ( result != 0 )
			printf("Exists.\n");
		else
			printf("Not exists.\n");
	}

	printf("Done.\n");


	printf("Neighbors() test.\n");

	while ( 1 )
	{
		idx_v_from = -1;
		printf("Enter idx_v_source | -1 to quit>");
		scanf("%d", &idx_v_from);

		if ( idx_v_from == -1 )
			break;

		result = Neighbors(g, idx_v_from, idxs_v_target);

		printf("V[%d]\'s neighbor list: [", idx_v_from);

		if ( result != 0 )
		{
			for ( idx_v_to = 0; idx_v_to < result; ++idx_v_to )
				printf("%d, ", idxs_v_target[idx_v_to]);

			printf("\b\b]\n");
		}
		else
			printf("empty]\n");
	}

	printf("Done.\n");


	Delete_Graph(g);
	g = 0;

	free(idxs_v_target);

	return 0;
}