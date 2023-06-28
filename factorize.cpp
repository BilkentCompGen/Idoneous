#include "bitpack.h"
#include "comparison.h"
#include "swa.h"
#include "lyndon.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string.h>
#include <algorithm>
#include <vector>

#define LEAF_COUNTING 0
#define INIT_PRINT 0
#define LEVEL_CONSTANT 3
#define ORDER_MAX ORDER_SIZE
#define MIN_GAP 10
#define ATL 20
#define NXBIG 500
using namespace std;


int blockCount = 0;



void getPositions( string s, list<long>& pos, int lorder=0 ){
    unsigned int n = s.size();
    for (unsigned int l = 0; l < n; )
    {
        unsigned int r = l;
	unsigned int p = l + 1;
        for (; r < n && charCmp( s[r] , s[p], lorder ) <= 0; ++r, ++p)
            if ( charCmp( s[r] , s[p] , lorder ) < 0 ) r = l - 1;

        while (l <= r)
        {
            l += p - r;
	   if( l < n ) pos.push_back(l);
        }
    }
}


int lynInit( lyndonWord& l , long minSize, int same = 0 ){
	int  level = 0;
	if( INIT_PRINT )
		cout << "Position: "<< l.start << ", Size: " << l.end - l.start << ", Order: " << l.order << ", lize"<< l.lynSize  <<endl;
//	l.order = lorder & (ORDER_MAX-1);
	if( l.end - l.start > minSize ){
		list<long> pos;
		pos.clear();
		getPositions( l.word->substr(l.start,l.end-l.start) , pos, (l.order + 1)%ORDER_MAX );
		long temp = 0;
		int size = pos.size();
		if( size > l.end - l.start)
		cout << "insanity devours us!" << endl;
		if( size > 0 ){
			l.lynSize = size+1;
			list<long>::iterator posptr =  pos.begin();
			l.lyndons =  new lyndonWord[size+1];  //(lyndonWord*) malloc( sizeof(lyndonWord) * size );
			for( int i = 0; i < size; i++){
				l.lyndons[i].word  = l.word;
				l.lyndons[i].start  = l.start+ temp;
				l.lyndons[i].end  = l.start+(*posptr);
				l.lyndons[i].lynSize  = 0;
				l.lyndons[i].order = (l.order + 1 ) % ORDER_MAX;
				temp = *posptr;
				advance(posptr, 1);
				l.lyndons[i].next = &(l.lyndons[i+1]);
			}
			l.lyndons[size].order = (l.order + 1 ) % ORDER_MAX;
			l.lyndons[size].word  = l.word;
			l.lyndons[size].lynSize  = 0;
			l.lyndons[size].start  = l.start+ temp;
			l.lyndons[size].end  = l.end;
			l.lyndons[size].next = l.next;

		}else{
			l.lynSize = 1;
			l.lyndons = new lyndonWord[1]; // (lyndonWord*) malloc( sizeof(lyndonWord) );
			l.lyndons[0].word  = l.word;
			l.lyndons[0].start = l.start;
			l.lyndons[0].end  = l.end;
			l.lyndons[0].next = l.next;
			l.lyndons[0].lynSize = 0;
			l.lyndons[0].order = (l.order + 1 ) % ORDER_MAX;
			size = 1;
		}
		same = size != 1 ? 0 : same +1 ;
		if( same < ORDER_MAX ){
			for( int i = 0; i < size+1; i++){
				int temp2 = lynInit( l.lyndons[i], minSize , same  );
				level = temp2 >= level ? temp2 + 1 : level;
			}
		}
	}
	l.level = level;
	if( INIT_PRINT )
		cout << "Level: " << level << ", Position: "<< l.start << ", Size: " << l.end - l.start << ", Order: " << l.order << ", lize"<< l.lynSize  <<endl;
	blockCount++;
	return level;
}



void iterate( lyndonWord& l ){
		cout << l.start<< "-"<< l.end <<": "// << strandPrint( l.word->substr(l.start,l.end-l.start) )
				 << "("<< l.level <<  ")[" << l.order <<"]" << ": " << strandPrint( l.word->substr( l.start, 5 ) )  << endl ;
		for( int i = 0; i < l.lynSize ; i++ ){
			iterate( l.lyndons[i]  );
		}
}

void lexispetialList( lyndonWord& l ){
	if ( l. level  == 0) return;
	unsigned char a  = l.word->at( l.start );
	unsigned char b  = l.word->at( l.start + 1);
	unsigned int x = a * 256 + b ;
	cout << l.end - l.start << " " <<  x  << endl ;
	for( int i = 0; i < l.lynSize ; i++ ){
		lexispetialList( l.lyndons[i]  );
	}

}


lyndonWord* getFirstBig( lyndonWord* l ){
	if( l == NULL ) return NULL;
	for( int i = 0; i < l->lynSize; i++){
		if( l->lyndons[i].level > 0 ){
			return &(l->lyndons[i]);
		}
	}

	lyndonWord* result = l->next;
	while ( result != NULL && (result -> level == 0) ) result = result->next;
	return result;
}

void getAnchor( lyndonWord* l1, lyndonWord* l2, vector<long>& anc , int k, long t1, long t2){
	lyndonWord* p1 = getFirstBig( l1 );
	lyndonWord* p2 = getFirstBig( l2 );
	while( p1 != NULL && p2 != NULL  ){
		if( p1->start > t1 || p2->start > t2 ){
			return;
		}else{
			if( p1->order != p2->order){
				if( p1->end - p1->start > p2->end - p2->start ){
					p1 = getFirstBig(p1);
				}else{
					p2 = getFirstBig(p2);
				}
			}else{
				int cmp = kmerCmp2( p1->word, p2->word, p1->start, p2->start, k, p1->order);
				if( cmp == 0 ){
					anc.push_back( p1->start );
					anc.push_back( p2->start );
					p1 = getFirstBig(p1);
					p2 = getFirstBig(p2);
				}else{
					if( cmp > 0 ^ (p1->end - p1->start >= p2-> end -p2 ->start) ){
						p2 = getFirstBig(p2);
					}else{
						p1 = getFirstBig(p1);
					}
				}


/*				if( cmp > 0 && p1->end - p1->start >= p2-> end -p2 ->start ){
					p1 = getFirstBig(p1);
				}else if( cmp < 0 && p1->end - p1->start <= p2-> end -p2 ->start ){
					p2 = getFirstBig(p2);
				}else{
					if( cmp == 0 ){
						anc.push_back( p1->start );
						anc.push_back( p2->start );
					}
					p1 = getFirstBig(p1);
					p2 = getFirstBig(p2);
				}
				*/
			}
		}
	}
}

lyndonWord* getIndex( lyndonWord* l, long start, int b ){
	if( l == NULL ) return NULL;
	if( l->start + b > start  ){
		return l;
	}
	if( l->end < start ) return getIndex(l->next, start, b);
	int i = 1;
	for( ; i < l->lynSize; i++){
		if( l->lyndons[i].start > start ) break;
	}
	return getIndex( &l->lyndons[i-1] , start, b);
}


void slices( lyndonWord* l, vector<lyndonWord*>& starts, int snum, int b){
  for( int i = 0; i * snum + b < l->end ; i++ ){
//    cout <<  i*snum << " " << l->start << endl;
    lyndonWord* lptr = getIndex(l, snum*i ,b) ;
    if( lptr != NULL ){
      starts.push_back( lptr );
//      cout << lptr->start << " " << lptr->end << " " << endl;
    }
  }
/*
	for( int i = 0; i < snum; i++){
		starts.push_back( getIndex(l, ((l->end)/snum)*i, b ) );
	}
*/
}

void getIntervals( vector<long>& l, long thr, vector<long>& out, int chain=2 ){
	if( l.size() <= 2*chain + 2 ) return;
	for( int i = 0; i < l.size()-2*chain-2; i++){
		bool ch = 1;
		for( int j = 0; j < chain && ch ; j++ )
			if( (l[i+2+2*j]-l[i+2*j]+thr < l[i+3+2*j]-l[i+1+2*j]) || l[i+3+2*j]-l[i+1+2*j]+thr < l[i+2+2*j]-l[i+2*j]   )
				ch = 0;

		bool bk = 0;
		if( !out.empty() ){
			for( int j = 0; j < chain &&  !bk; j++){
				if( out.back() == l[i+1+2*j] )
					bk = 1;
			}
		}
		if( ch  ){
			if(  bk ){
				out.pop_back();
				out.pop_back();
			}else{
				out.push_back(l[i]);
				out.push_back(l[i+1]);
			}
			out.push_back( l[i+2*chain] );
			out.push_back( l[i+2*chain+1] );
		}
	}
}
