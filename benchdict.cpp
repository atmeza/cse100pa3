/**
 * Filename: benchdict.cpp
 * Author: Alex Meza
 * Userid: cs100vbj
 * Description: personal time testing file
 * Date: August 22, 2016
 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include <fstream>
#include <sstream>

int main(int argc, char*argv[]){


//check arguments
   if(argc!=5){

       std::cout<<"Incorrect amount of args";
       return -1;
   }

    std::cout<<"DictionaryTrie\n";
    

    std::ifstream in;//create stream
    in.open(argv[4],std::ios::binary);//open file
    DictionaryTrie* mydict = new DictionaryTrie();//create dictionary trie



    int its = atoi(argv[3]);//for this many iterations
    unsigned int step = atoi(argv[2]);//step size
    unsigned int min = atoi(argv[1]);//min size
    Timer t;
    unsigned int count = 0;
    long long time = 0;

    for(int i = 0; i < its;i++){

       
        if(i==0){
            Utils::load_dict(*mydict,in,min);
            count+= min;
        }
        else{
            Utils::load_dict(*mydict,in,step);
            count+=step;
        }

        for(int k = 0;k<10;k++){

        t.begin_timer();//begin timer

        mydict->find("aaaaaaaaaa");
        mydict->find("bbbbbbbb");
        mydict->find("why are wehywerln");
        mydict->find("my name is alexander");
        mydict->find("asldfjlaskdfvglksdfn");
        mydict->find("welkjqlknlsdkfgjdlb");
         mydict->find("ccccccccccccc");
        mydict->find("ddddddddddd");
        mydict->find("mzzzzzzzzzzzzzzz");
        mydict->find("asldfjlsdflsadffmsf");
        mydict->find("welkjqlknlsdkfgjsdfsfdlb");
        if(!mydict->find("man")){

            return -1;}
        

         time += t.end_timer();
        }
        std::cout<<count<< "\t";//print out size
        std::cout<<time/10<<"\n";//print out time to search
        
    }

    std::cout<<"\n";//now to next data structure
    delete mydict;




    in.clear();//
    in.seekg(0,std::ios::beg);//return back to beginning of file
    time = 0;
    count = 0;
    DictionaryHashtable* hdict = new DictionaryHashtable();
    std::cout<<"DictionaryHashtable\n";
    for(int i = 0; i <its;i++){

       if(i== 0){
            Utils::load_dict(*hdict,in,min);
            count+=min;
       }
       else{
           Utils::load_dict(*hdict,in, step);
            count+=step;
        }
        for(int k = 0;k<10;k++){
//do it 10 times t oget average

        t.begin_timer();//begin timer

        hdict->find("aaaaaaaaaa");
        hdict->find("bbbbbbbb");
        hdict->find("why are wehywerln");
        hdict->find("my name is alexander");
        hdict->find("asldfjlaskdfvglksdfn");
        hdict->find("welkjqlknlsdkfgjdlb");
         hdict->find("ccccccccccccc");
        hdict->find("ddddddddddd");
        hdict->find("mzzzzzzzzzzzzzzz");
        hdict->find("asldfjlsdflsadffmsf");
        hdict->find("welkjqlknlsdkfgjsdfsfdlb");
        time += t.end_timer();
        }
        std::cout<<count<< "\t";//print out size
        std::cout<<time/10<<"\n";//print out time to search

    }

    std::cout<<"\n";//now to next data structure
    delete hdict;


    in.clear();//
    in.seekg(0,std::ios::beg);//return back to beginning of file

    count = 0;
    DictionaryBST* bdict = new DictionaryBST();
    std::cout<< "DictionaryBST"<<"\n";
    for(int i = 0; i <its;i++){
     //for requested iterations   
        if(i==0){
            count+=min;
            Utils::load_dict(*bdict,in,min);
            
        }
        else{
            Utils::load_dict(*bdict,in,step);
            count+=step;
        }
       
        for(int k = 0;k<10;k++){
//for average of 10 times

        t.begin_timer();//begin timer

        bdict->find("aaaaaaaaaa");
        bdict->find("bbbbbbbb");
        bdict->find("why are wehywerln");
        bdict->find("my name is alexander");
        bdict->find("asldfjlaskdfvglksdfn");
        bdict->find("welkjqlknlsdkfgjdlb");
         bdict->find("ccccccccccccc");
        bdict->find("ddddddddddd");
        bdict->find("mzzzzzzzzzzzzzzz");
        bdict->find("asldfjlsdflsadffmsf");
        bdict->find("welkjqlknlsdkfgjsdfsfdlb");
        time += t.end_timer();
        }
         std::cout<<count<< "\t";//print out size
        std::cout<<time/10<<"\n";//print out time to search

    }
    delete bdict;
    std::cout<<"\n";//now to next data structure
    std::cout<<"Finished Running Times";



}
