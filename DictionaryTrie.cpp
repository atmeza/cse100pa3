/**
 * Filename: DictionaryTri.cpp
 * Author: Alex Meza
 * Userid: cs100vbj
 * Description: multi-tri structure 
 * Date: August 22, 2016
 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <queue>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}

DictionaryTrie::~DictionaryTrie(){

    clear(root);
}

void DictionaryTrie::clear(DTNode* node){
    
    for(auto i:node->children){
        clear(i);
    }
    delete node;
    for(auto n:node->children){
        if(n!=NULL){
            n = NULL;
        }
    }
    node = NULL;

}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    if(word.length()==0){return false;}//if empty word return false

    if(0==root){//if root is null
        
        root = new DTNode(" ",0); //starts at " "

    }

    unsigned int h = 1;//level traversed
    DTNode* temp = root;//for traversing through trie
    DTNode* temp2;//for inserting into children 
    bool existed = false;//check if path node already existed


    for(;h<word.length()+1;h++){//for each level
        
        for(auto tnode: temp->children){//for all children at that level

            if(0==word.compare(0,h, tnode->word)){//if DTNode exists with path of word
                existed = true;
                if(h==word.length()){//if word is already in trie
                    if(tnode->isWord){
                    return false;}

                    tnode->isWord = true;
                }
                

                temp = tnode;//keep track of this node
                break;
            }
        }
        if(!existed){//if corresponding DTNode didnt exist
        
                
                temp2 = new DTNode(word.substr(0,h),0);
                temp->children.insert(temp->children.begin(),temp2);//create DTNode
                temp = temp2;
            if (word.length() == h){//if at final letter make leaf 
                temp2->isWord = true;
                temp2->freq = freq;
                break;//optional break?
            }

        }
        existed = false;//return to false    

    }
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    DTNode* temp = root;//traversing from root
    unsigned int h = 1;//starting at height 0
    bool check; //indicate whether path to word existed

    for(;h<word.length()+1;h++){//for each character
    
        for(auto tnode: temp->children){//for each of the children
            
            if(0==word.compare(0,h, tnode->word)){//if matching node on path
                check = true;//mark true
                temp = tnode;//next child to check
                break;
            }
        
        }
        if(!check){
            return false;//not in trie
        }
        check = false;

    }
  return true;//was not a word
}






/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  //for sorting nodes according to frequencies
  std::priority_queue<DTNode*,std::vector<DTNode*>,DTPtrComp> pq;

    DTNode* temp = root;//get to node with desired path
    unsigned int j = 1;//count
    bool check= false;//check if found within children
    for(;j<prefix.length()+1;j++){//for length of prefix
     //for all of children   
        for(auto tnode: temp->children){
           
            
            if(0==prefix.compare(0,j,tnode->word)){
             
                check = true;//found child
                temp = tnode;//traverse tri
                break;

            }
            
        }
        if(!check){//if didnt find child
            return words;
        }
        

    }
    //if node exists with path of prefix doesnt exist
    if(temp->word!=prefix){return words;}
    if(temp->isWord){//if that node is a word itself
        pq.push(temp);
    }
    //bfs search
    findCompletions(temp,pq);

  unsigned int i = 0;//counter
  for(;i<num_completions;i++){//for however many completions desired
      
      if(pq.empty()){//if no words left 
        break;
      }
      words.insert(words.end(),pq.top()->word);//get first in pq
      pq.pop();//take out last

  }
 return words;
}

/* Destructor */
