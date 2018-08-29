/*===============================================================================
    How Does it work
    -----------------
    like every algorithm there is a data base and a flow

    (1) data base 

        (1.1) Vertics group
              a vertic is one node in the graph

        (1.2) Edges group
              an Edge is a set of two vertics
              every edge has a weight and a direction.
              e.g (1,2) is the edge from vertic 1 to vertic 2
                  |(1,2)|=30 the weight of edge from vertic 1 to 2 is 30
              
        (1.3) setteled group
              holds all setteled vertics.
              a setteled vertic is one that the functions d()
              and pi() been setteled/established for it.
              d(vertic) - to calculate d() for a vertic 
                          u should add the weight of the edge to the d() 
                          of the vertic from which u are traveling to that vertic
                          e.g. if d() for vertic 1 is 12 i.e. d(1)=12
                               and the vertic you are calculating d() for is 2
                               and the edge's weight is 15 i.e. |(1,2)|=15
                               then d(2)=d(1) + |(1,2)| = 12 + 15 = 27
              pi(vertic) - when calculatin d() for a vertic if the result is smaller then the 
                           vertics d() then pi() for that vertic is set to the vertic from which 
                           the d() was calculated.
                           e.g. if d(1)=12 and d(2)=30 and |(1,2)|=15
                           i.e. d(2)=27 and since 27 < 30 then pi(2)=1
                           if it was equal or bigger then pi(2) wouldnt change.
                           
        (1.4) unsetteled group
              holds all unsetteled vertics 
              unsetteled vertic is one that the functions d() and pi() were not 
              yet established for it.

    (2) Flow

    dijekstra(){

        initialize setteled group to empty 
        initialize unsetelled group to the starting vertic.
        initialize the starting vertic to 
          d(starting vertic)=0 and 
          pi(starting vertic)=starting vertic
        all other vertics to 
          d(vertic)=inifinity and 
          pi(vertic)=unknown.

        while (unsetteled group NOT empty) {
            (2.1) choose the smallest d(vertic) from the unsetteled group.
            (2.2) move this vertic from unsetteled group to setteled.
            (2.3) add this  vertic's predecessors to unsetteled group. 
            (2.4) relax predecessors.
        }
    }

    all that remains is to explain what predecessors are 
    and what is relaxation.

    predecessorse - 
       are the verticses accesable from the a certein vertic.
       i.e. if you can travell from vertic 1 to vertices : 4,6 and 9
       then 4,6 and 9 are vertic 1 predecessors.

    relaxation - 
       is the process of calculating a vertic's predecessor's
       functions d() and pi() 
                          
  ===========================================================================*/



#include <stdlib.h>


//====================================================
//     declarations 
//====================================================
struct vertic;
struct edge;
struct vertic_group;
struct edge_group;
struct graph;

//====================================================
//     structures 
//====================================================
struct vertic{
    int num;
};

struct edge{
    struct vertic* s;
    struct vertic* t;
};


struct vertic_group{
    struct vertic* v;
    int v_size;
};

struct edge_group{
    struct edge* e;
    int e_size;
};

struct graph{
    struct edge_group*   E;
    struct vertic_group* V;
};

//====================================================
//     functions
//====================================================
struct vertic*
init_vertic(int n)
{
    struct vertic* v;

    v = (struct vertic*)malloc(sizeof(struct vertic));
    v->num = n;
    return v;
}

struct edge*
init_edge(struct vertic* s, 
          struct vertic* t)
{
    struct edge* e;

    e = (struct edge*)malloc(sizeof(struct edge));
    e->s = s;
    e->t = t;

    return e;
}

void
del_vertic(struct vertic* v)
{
    free(v);
}

void
del_edge(struct edge* e)
{
    del_vertic(e->s);
    del_vertic(e->t);
    free(e);
}

struct vertic_group*
init_vertic_group(int size)
{
    struct vertic_group* vg;

    vg = (struct vertic_group*)malloc( sizeof(struct vertic_group) );
    vg->v = (struct vertic*)malloc(sizeof(struct vertic) * size);
    vg->v_size = size;

    return vg;
}

struct edge_group*
init_edge_group(int size)
{
    struct edge_group* eg;

    eg = (struct edge_group*)malloc( sizeof(struct edge_group) );
    eg->e = (struct edge*)malloc(sizeof(struct edge) * size);
    eg->e_size = size;

    return eg;
}

void
del_edge_group(struct edge_group* eg)
{
    free(eg);
}

void
del_vertic_group(struct vertic_group* vg)
{
    free(vg);
}


struct graph*
init_graph(int e_size, 
           int v_size)
{
    struct graph* g;

    g = (struct graph*)mallco(sizeof(struct graph));

    g->E = init_edge_group(e_size);
    g->V = init_vertic_group(v_size);

    return g;
}

void
del_graph(struct graph* g)
{
    free(g->E);
    free(g->V);
    free(g);
}





