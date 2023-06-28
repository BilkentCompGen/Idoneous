#include <string>

using namespace std;
unsigned int complications[] = {0,0xC0};
//unsigned int complications[] = {0,0x80,0xC0,0x40};

int complicatedCmp(const char *p1, const char *p2, unsigned int complication=0  ){
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;
  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0' || c2 == '\0' )
        return (0x00FF & c1) - (0x00FF & c2);
//        return (0x00D0 & c1) - (0x00D0 & c2);
    }
  while (c1 == c2);
  return (complications[complication] ^ (0x00FF & c1)) - (complications[complication] ^ (0x00FF & c2)) ;
//  return (complications[complication] ^ (0x00D0 & c1)) - (complications[complication] ^ (0x00D0 & c2)) ;
}

int charCmp( char c1, char c2, unsigned int complication=0 ){
        if( c1 == '\0' || c2 == '\0' ) return (0xFF & c1) - (0xFF & c2);
        return  (complications[complication] ^ (0x00FF & c1)) - (complications[complication] ^ (0x00FF&c2)) ;
//        return  (complications[complication] ^ (0x000D0 & c1)) - (complications[complication] ^ (0x00D0&c2)) ;
}

int min( int a, int b){
	return a < b ? a : b;
}

int kmerCmp( const char *p1, const char *p2, int k, unsigned int complication=0){
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	for(int i = 0; i < k; i++){
		if( s1[i] != s2[i] ){
		  return (complications[complication] ^ (0x00FF & s1[i])) - (complications[complication] ^ (0x00FF & s2[i])) ;
//		  return (complications[complication] ^ (0x00D0 & s1[i])) - (complications[complication] ^ (0x00D0 & s2[i])) ;
		}
	}
	return 0;
}


int kmerCmp2( string *p1, string *p2, long st1, long st2, int k, unsigned int complication){
	const unsigned char *s1 = (const unsigned char *) p1->substr( st1, k ).c_str();
	const unsigned char *s2 = (const unsigned char *) p2->substr( st2, k ).c_str();
        for(int i = 0; i < k; i++){
                if( s1[i] != s2[i] ){
                  return (complications[complication] ^ (0x00FF & s1[i])) - (complications[complication] ^ (0x00FF & s2[i])) ;
//                return (complications[complication] ^ (0x00D0 & s1[i])) - (complications[complication] ^ (0x00D0 & s2[i])) ;
                }
        }
        return 0;
}
