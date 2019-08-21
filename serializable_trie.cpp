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

   //helper function
   void buildSerialTrie(trieNode *root, string &serialTrie)
   {
       if(root->isValidWord)
          serialTrie.push_back(']');
       unordered_map<char, trieNode*> &children = root->children;
       for(auto child : children)
       {
           serialTrie.push_back(child.first);
           buildSerialTrie(child.second, serialTrie);
       }
       serialTrie.push_back('>');
   }

   //helper function
   int stringToTrie(trieNode *node, string &serialTrie, int &read)
   {
        int wordSeen = 0;
        if(serialTrie[read] == ']')
        {
           node->isValidWord = 1;
           wordSeen++;
           read++;
        }
        else node->isValidWord = 0;


        unordered_map<char, trieNode*> &childMap = node->children;
        while(serialTrie[read] != '>')
        {
            char ch = serialTrie[read++];
            childMap[ch] = new trieNode();
            wordSeen += stringToTrie(childMap[ch], serialTrie, read);
        }
        read++;
        node->wordsWithPrefix = wordSeen;
        return wordSeen;
   }

public:

   //used to construct an empty trie.
   TrieDS()
   {
      root = new trieNode();
      totalWords = 0;
   }

   //Used to construct a trie initialized with a list of words.
   TrieDS(vector<string> words)
   {
       totalWords = 0;
       root = new trieNode();
       for(string word : words)
       {
       	  insertWord(word);
       }
   }

   //Used to construct a trie using an existing trie given in serial format.
   TrieDS(string serialTrie)
   {
       root = new trieNode();
       int read = 0;
       totalWords = stringToTrie(root, serialTrie, read);
   }

   //used to insert a word in the trie.
   void insertWord(string word)
   {
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
   vector<string> trieToList()
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

   string trieToString()
   {
       string serializedTrie;
       buildSerialTrie(root, serializedTrie);
       return serializedTrie;
   }

};

int main()
{
    /*
     *THIS PROGRAM USES THE TEST DATA
     *TO BUILD A TRIE FOR THE GIVEN DATA
     *THEN IT CONVERTS THE TRIE INTO ITS
     *SERIALIZED FORM AND WRITES IT TO A FILE
     */
    freopen ("TEST_DATA.txt", "r", stdin);
    freopen ("SERIAL_FORM.txt", "w", stdout);

    vector<string> input;
 	string word;

 	cin>>word;
 	while(word != "#END#")
    {
       input.push_back(word);
       cin>>word;
    }

 	TrieDS *myTrie = new TrieDS(input);
 	cout<<myTrie->trieToString();
 	return 0;
}
