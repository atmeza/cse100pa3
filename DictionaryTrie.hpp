/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <queue>
#include <iostream>
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here


 
  class DTNode {//Inner class Trie Node

    friend bool comp(DTNode* one, DTNode* other);
    
  public:

        std::string word;
        unsigned int freq;//stores freq if is a word
        bool isWord;//if the DTNode is in the dictionary
        std::vector<DTNode*> children;//path to children
        //constructor for DTNode
      DTNode(std::string dword, int dfreq):word(dword),freq(dfreq), isWord(false), children(){}
    
        bool operator<(const DTNode& other){
            return freq<other.freq;
        }

  };
 
 bool comp (DTNode* one, DTNode* other);



 //comparator for priority queue
 class DTPtrComp {
 public:
    bool operator()(DTNode*& lhs, DTNode*& rhs) const {
        return *lhs<*rhs;
    }
 };


//root of tri
    DTNode* root;

    
/*BFS
 *Recurssive method that goes through children and their children checking
 * if they are a word and if so adds them to queue
 */
void findCompletions(DTNode* tnode, std::priority_queue<DTNode*,std::vector<DTNode*>,DTPtrComp>& pq){

     
     //for all children of node 
   for(auto node: tnode->children){
       findCompletions(node, pq);//do same for children
        if(node->isWord){
            pq.push(node);//if children are a word add to pq
            

        }
     
   }

}

    void clear(DTNode* node);
    
};
#endif // DICTIONARY_TRIE_HPP
