#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string.h>
#include <algorithm>
#include "lyndon.h"

void selfContained( lyndonWord l);
int lynInit( lyndonWord& l , long minSize, int same = 0 );
void getPositions( string s, list<long>& pos, int lorder=0 );
void iterate( lyndonWord& l );
void lexispetialList( lyndonWord& l);
//void numberAndSize( lyndonWord l, int* numbers, int* sizes);
//void countLeafSizes( lyndonWord l , int* counters  );
//void countLeafsParentLevel( lyndonWord l , int counters[]  );
//void search( lyndonWord l, string pattern, int lorder = 0 );
//void allMinCounts( lyndonWord& lyn, vector<int>* mins, vector<string> strand, int k , vector<int>* hitblocks);
//void findAllWr( lyndonWord& lyn, vector<int>& mins, string& strand, int k , int minimumRange , vector<int>& order, vector<long>& hits);
void getAnchor( lyndonWord* l1, lyndonWord* l2, vector<long>& anc , int k, long t1, long t2);
void getIntervals( vector<long>& l1, long thr, vector<long>& out , int chain=2 );
void slices( lyndonWord* l, vector<lyndonWord*>& starts, int snum, int b);
