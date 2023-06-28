enum order{ACTG = 0, TGCA , ORDER_SIZE = 2};
//enum order{ACTG = 0, TGCA ,GTCA, CAGT, ORDER_SIZE = 4};

int kmerCmp( const char *p1, const char *p2, int k, unsigned int complication=0);
int kmerCmp2( string *p1, string *p2, long st1, long st2, int k, unsigned int complication);
int complicatedCmp(const char *p1, const char *p2, unsigned int complication=0  );
int charCmp( char c1, char c2, unsigned int complication=0 );
int min( int a, int b);
