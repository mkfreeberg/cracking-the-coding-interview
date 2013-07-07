#include <iostream>
#include <cstring>
using namespace std;

bool isUnique1(string s) {
    bool a[256];
    memset(a, 0, sizeof(a));
    bool not_unique = false;
    for(string::iterator iter = s.begin(); !not_unique && iter != s.end(); ++iter) {
        int v = (int) *iter;
        if (a[v]) not_unique = true; else a[v] = true;
    }
    return !not_unique;
}

#include <boost/cstdint.hpp>

bool isUnique2(string s) {
    boost::uint32_t a[8];
    memset(a, 0, sizeof(a));
    bool not_unique = false;
    for(string::iterator iter = s.begin(); !not_unique && iter != s.end(); ++iter) {
        int v = (int) *iter;
        int idx = v/32, shift=v%32;
        if(a[idx] & (1<<shift)) not_unique = true; else a[idx] |= (1<<shift);
    }
    return !not_unique;
}

#include <boost/algorithm/string.hpp>

bool isUnique3(string s) {      /* You were assuming this was lowercase so I made this case-insensitive */
    boost::uint32_t check = 0;  /* Exercise 1.1 does not specify whether or not that is the requirement */
    bool not_unique = false;
    for(string::iterator iter = s.begin(); !not_unique && iter != s.end(); ++iter) {
        int v = boost::algorithm::to_lower( *iter ) - 'a';
        if(check & (1<<v)) not_unique = true; else check |= (1<<v);
    }
    return !not_unique;
}

#include <set>

bool isUnique4(string String) { /* Exercise 1.1 says "What if you cannot use data structures? From this I'm */
                                /* inferring that the interviewer would want to see both implementations    */
                                /* This one uses a data structure of std::set, which presumably works in    */
                                /* O(log n) time */
    set<char> Set;
    bool not_unique = false;
    for(string::iterator iter = String.begin(); !not_unique && iter != String.end(); ++iter) {
        if ( Set.find( *iter ) == Set.end() ) Set.add( *iter ); else not_unique = true;
    }
    return !not_unique;
}

int main( int argc, char *argv[] ) {
    if ( argc < 2 ) {
        cout << "Syntax: unique_1_1 {string}" << endl;
    } else {
        string TheString( argv[1] );
        cout << "1: \"" << TheString << "\" is " << (isUnique1(TheString)?"unique":"not unique") << "." << endl;
        cout << "2: \"" << TheString << "\" is " << (isUnique2(TheString)?"unique":"not unique") << "." << endl;
        cout << "3: \"" << TheString << "\" is " << (isUnique3(TheString)?"unique":"not unique") << "." << endl;
        cout << "4: \"" << TheString << "\" is " << (isUnique4(TheString)?"unique":"not unique") << "." << endl;
    }
    return 0;
}
