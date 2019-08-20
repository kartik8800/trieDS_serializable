///author : Kartik Arora
#include<bits/stdc++.h>
using namespace std;

//This structure is used to represent a node of the trie.
struct trieNode
{
    //indicates if the word ending here is a valid word.
    bool isValidWord;
    //number of words have the prefix that is represented by this node.
    int wordsWithPrefix;
    //represent all child nodes of this node.
    unordered_map
       <char,trieNode*> children;

    trieNode()
    {
       isValidWord = false;
       wordsWithPrefix = 0;
    }

};

//This class represents a generic trie data structure
class TrieDS
{
private:

   trieNode *root;

   int totalWords;

   //helper function that traverse the trie and finds all word present in trie.
   void treeDepthTraversal(trieNode *currentNode,
                   vector<string>& trieToString,string prefix)
   {
   	 if(currentNode->isValidWord)
   	 {
   	 	trieToString.push_back(prefix);
   	 }
   	 for(auto p : currentNode->children)
   	 {
   	 	prefix.push_back(p.first);
   	 	treeDepthTraversal(p.second, trieToString, prefix);
   	 	prefix.pop_back();
   	 }
   }

public:

   //used to construct an empty trie.
   TrieDS()
   {
      root = NULL;
      totalWords = 0;
   }

   //Used to construct a trie initialized with a list of words.
   TrieDS(vector<string> words)
   {
       totalWords = 0;
       for(string word : words)
       {
       	  insertWord(word);
       }
   }

   //used to insert a word in the trie.
   void insertWord(string word)
   {
      if(totalWords == 0)
      {
          root = new trieNode();
      }
      trieNode *currentNode = root;
      for(int i = 0; i < word.length(); i++)
      {
        currentNode->wordsWithPrefix++;
      	unordered_map<char,trieNode*>& childMap = (currentNode->children);
      	auto it = childMap.find(word[i]);
      	if(it == childMap.end())
      	{
      	   currentNode = new trieNode();
      	   childMap[word[i]] = currentNode;
      	}
      	else
      	{
      		currentNode = childMap[word[i]];
      	}
      }
      currentNode->wordsWithPrefix++;
      currentNode->isValidWord = true;
      totalWords++;
   }

   //gives the total number of words currently present in the trie.
   int numberOfWordsInTrie()
   {
       return totalWords;
   }

   //Used to convert the trie to a list of words(serialization).
   vector<string> serializeTrie()
   {
   	  vector<string> trieToString;
   	  treeDepthTraversal(root, trieToString, "");
   	  return trieToString;
   }

   //check to see if a word is present in the trie.
   bool findWord(string word)
   {
      int countOfWord = wordsWithThePrefix(word,0);
      if(countOfWord>0)
         return true;
      else return false;
   }

   //Number of words in the trie the have a given prefix.
   int wordsWithThePrefix(string prefix, int calledBy = 1)
   {
      if(root==NULL)
              return 0;
      trieNode *currentNode = root;
      for(int i = 0; i < prefix.length(); i++)
      {
        unordered_map<char,trieNode*>& childMap = (currentNode->children);
      	auto it = childMap.find(prefix[i]);
      	if(it == childMap.end())
      	   return 0;
      	else
      		currentNode = childMap[prefix[i]];
      }
      if(calledBy||currentNode->isValidWord)
           return currentNode->wordsWithPrefix;
      else return 0;
   }

};

int main()
 {
 	vector<string> input;
 	input.push_back("banana");
 	input.push_back("apple");
 	input.push_back("litchi");
 	input.push_back("blueberry");
 	input.push_back("apricot");
 	TrieDS *myTrie = new TrieDS(input);
 	vector<string> output = myTrie->serializeTrie();
 	for(string s: output)
 	          cout<<s<<endl;
    cout<<myTrie->wordsWithThePrefix("ap")<<endl;
    cout<<myTrie->findWord("apple")<<endl;
 	return 0;
 }
