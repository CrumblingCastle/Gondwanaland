#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <iterator>
using namespace std;

bool BLOCKED=0;
int M, N, i, feed, val, valnext, valprev, res=0, pos=0;
tuple<int, int, int> kwstas; // o kwstas feedarei dedomena
vector< tuple<int, int, int> > meres;
vector< tuple<int, int, int> >::iterator ptr;

void check_merge(tuple<int, int, int> t){
    // get val
    val = get<0>(t);
    cout << "new proc starts for: " << val << " ,position: " << pos << "\n";

    // negative val - go next or finish in case of tail
    if (val < 0){
        ptr ++;
        cout << val << " ,of position " << pos << " is a negative.\n";
        // if not tail
        if( ptr != meres.end() ){
             pos++;
             cout << "also is not tail. calling proc for pos " << pos << "\n";
             check_merge(meres[pos]);
        }
        
        else{
            cout << "TAIL ";
        }

        cout << "proc exiting\n";
        exit(0);
    }

    // SPECIAL - positive head
    if(ptr == meres.begin()){
        while(BLOCKED==0){
            
            // head merged all!
            if(meres.size() == 1){
                exit(0);
            }

            valnext = get<0>(meres[pos+1]);
            
            // next is merging
            if ( valnext + val >= 0){
                // loot next
                val += valnext;
                get<1>(t) += get<1>(meres[pos+1]); //get<1>(t)++; beltiwsh
                // res is always best
                if (get<1>(t) > res){
                    res = get<1>(t);
                }
                // delete next and return ptr
                ptr ++;
                meres.erase(ptr);
                ptr --;
            }
            
            // next is NOT merging - surely a negative - i'm BLOCKED
            else{
                ptr++; pos++;
                check_merge(meres[pos]);
                exit(0);
            }
        }
    }

    // surely a positive val - NOT HEAD - NOT TAIL
    BLOCKED = 0;
    while(BLOCKED == 0 && ptr < meres.end()-1 && ptr > meres.begin() ){
        valprev = get<0>(meres[pos-1]); //ektos an head
        valnext = get<0>(meres[pos+1]); //ektos an tail

        // next is better
        if ( valnext >= valprev ){
            // next is merging
            if ( valnext + val >= 0){
                // loot next
                val += valnext;
                get<1>(t) += get<1>(meres[pos+1]);
                // res is always best
                if (get<1>(t) > res){
                    res = get<1>(t);
                }
                // delete next and return ptr
                ptr ++;
                meres.erase(ptr);
                ptr --;
            }
            
            // next is NOT merging - surely a negative
            else{
                ptr++; pos++;
                check_merge(meres[pos]);
                BLOCKED = 1;
                
            }
        }
        
        // prev is better
        else{
            // prev is merging
            if ( valprev + val >= 0){
                // loot prev
                val += valprev;
                get<1>(t) += get<1>(meres[pos-1]);
                // res is always best
                if (get<1>(t) > res){
                    res = get<1>(t);
                }
                // delete prev and return ptr
                ptr--; pos--;
                meres.erase(ptr);
            }
            
            // prev is NOT merging - surely a negative
            else{
                ptr++; pos++;
                check_merge(meres[pos]);
                BLOCKED=1;
            }
        }
    }

    // SPECIAL - positive tail
    if(ptr == meres.end()-1){
        // while tail has not merged all
        while(meres.size() != 1){

            valprev = get<0>(meres[pos-1]);
            
            // prev is merging
            if ( valprev + val >= 0){
                // loot prev
                val += valprev;
                get<1>(t) += get<1>(meres[pos-1]);
                // res is always best
                if (get<1>(t) > res){
                    res = get<1>(t);
                }
                // delete prev and return ptr
                ptr --; pos--;
                meres.erase(ptr);
            }
            
            // prev is NOT merging - surely a negative - i'm BLOCKED
            else{
                exit(0);
            }
        }
    }
    exit(0);
}

int main() {

    cin >> M;
    meres.reserve(M);
    cin >> N;
    cout << "----------------------\n";

    //bazw oles ties meroules sto vector mou
    for (i=0; i < M; i++){
        cin >> feed;
        kwstas = make_tuple(N-feed, 1, 0);
        meres.push_back(kwstas);
    }

    cout << "----------------------\n";
    cout << "size is: " << meres.size() << "\n";
    for (i=0; i < M; i++){
        cout << i << " " << get<0>(meres[i]) << "\n";
    }
    cout << "----------------------\n";

    ptr = meres.begin();
    check_merge(meres[0]);
    cout << "----------------------\n";
    cout << "I've exited! Your spicy result is" << res << "\n";

    cout << "----------------------\n";
    cout << "size is " << meres.size() << "\n";
    for (i=0; i < M; i++){
        cout << get<1>(meres[i]) << " " << get<0>(meres[i]) << "\n";
    }
}
