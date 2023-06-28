#include <iostream>

struct lyndonWord{
        string* word;
        long start;//unsigned int start;
        long end;//unsigned int end;
        lyndonWord* lyndons;
        int lynSize = 0;
        lyndonWord* next;
        int level;
        unsigned int order = 3;
        lyndonWord(){
                word = NULL;
                start = 0;
                end = 0;
                lynSize = 0;
                lyndons = NULL;
                next = NULL;
        }


        lyndonWord(string* word_ ){
                word = word_;
                start = 0;
                end = word->size();
                lynSize = 0;
                lyndons = NULL;
                next = NULL;
        }
        lyndonWord(string* word_, long start_, long end_ ){
                word = word_;
                start = start_;
                end = end_;
                lyndons = NULL;
                next = NULL;
                lynSize = 0;
        }
        lyndonWord( const lyndonWord& copy){
                word = copy.word;
                start = copy.start;
                lyndons = copy.lyndons;
                next = copy.next;
                level = copy.level;
                order = copy.order;
                end = copy.end;
                lynSize = copy.lynSize;
        }

        ~lyndonWord(){
                if( lyndons != NULL){
                        delete[]  lyndons;
                }
        }
};
