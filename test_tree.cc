// Sam Gustafsson

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

namespace {

template <typename TreeType>
void nodeRemove(int & remove_calls, int & recursive_calls, int& nodes_removed, const string &seq_filename, TreeType &a_tree){
  ifstream s_file;
  s_file.open(seq_filename, ios::in);

  int every_other_seq = 0;
  int a_treeRemove = 0;
  string space_bar = " ";

  while (getline(s_file, space_bar)){
    if (every_other_seq % 2 == 0){ //if it is even, for odd it would be % 2 != 0.
      remove_calls++;
      a_treeRemove = a_tree.removeT(recursive_calls, space_bar);

      nodes_removed = nodes_removed + a_treeRemove;
    }

    every_other_seq++;
  }
  s_file.close();
}

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part 2.2

  string db_line;
  db_line.substr(0, db_line.length() - 2); //reading the line with the two slashes
  string junk_line;

  ifstream my_file (dbx_filename); //reding the file that the user puts through
  for (int i = 0; i < 10; i++){ //skipping the first 10 lines
    getline(my_file, junk_line);
  }
  while (getline(my_file, db_line)){
    stringstream ss(db_line);
    string an_enz_acro = db_line.substr(0, db_line.find('/'));
    string a_rec_seq;

    getline(ss, an_enz_acro, '/'); //getting the acronyms and separating it by the '/'

    while(getline(ss, a_rec_seq, '/')){ //getting the sequence of the acronyms and separating it by the '/'
      if (a_rec_seq.length() > 0){
        SequenceMap map(a_rec_seq, an_enz_acro);
        a_tree.insert(map); //insert map into the tree.
      }
    } 
  }

  //------------------------------------

  ifstream my_file2;
  my_file2.open(seq_filename, ios::in);

  //2. Prints the number of nodes in your tree 𝑛.
  cout << "2a: " << a_tree.nodeCount() << endl;

  //3. Computes the average depth of your search tree, i.e. the internal path length divided by 𝑛.
  //a. Prints the average depth.
  //b. Prints the ratio of the average depth to log! 𝑛. E.g., if average depth is 6.9 and log! 𝑛 =
  //5.0, then you should print ".$ = 1.38.
  cout << "3a: " << a_tree.averageDepth() << endl;
  cout << "3b: " << a_tree.averageDepth() / log2(a_tree.nodeCount()) << endl;

  //4. Searches (find()) the tree for each string in the sequences.txt file and counts the total number 
  //of recursive calls for all executions of find().
  //a. Prints the total number of successful queries (number of strings found).
  //b. Prints the average number of recursion calls, i.e. #total number of recursion calls / number of queries.
  int match = 0;
  int calls = 0;
  string space_bar = " ";

  while (getline(my_file2, space_bar)){
    match = match + a_tree.findMatches(space_bar);
    calls = calls + a_tree.findCalls(space_bar);
  }
  my_file2.close();

  cout << "4a: " << match << endl;
  //using static_cast to convert calls and match to float
  float success = (static_cast<float>(calls) / static_cast<float>(match));
  cout << "4b: " << success << endl;

  //5. Removes every other sequence in sequences.txt from the tree and counts the total number of
  //recursion calls for all executions of remove().
  //a. Prints the total number successful removes.
  //b. Prints the average number of recursion calls, i.e. #total number of recursion calls / number of remove calls.
  int removed_calls = 0;
  int removed_nodes = 0;
  int recursive_calls = 0;

  nodeRemove(removed_calls, recursive_calls, removed_nodes, seq_filename, a_tree);

  float average_removed_calls = (static_cast<float>(recursive_calls) / static_cast<float>(removed_calls));
  cout << "5a: " << removed_nodes << endl;
  cout << "5b: " << average_removed_calls << endl;

  //Redo steps 2 and 3:
  //a. Prints number of nodes in your tree.
  //b. Prints the average depth.
  //c. Prints the ratio of the average depth to log! 𝑛.
  cout << "6a: " << a_tree.nodeCount() << endl;
  cout << "6b: " << a_tree.averageDepth() << endl;
  cout << "6c: " << a_tree.averageDepth() / log2(a_tree.nodeCount()) << endl;



}  // namespace
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);

  return 0;
}

