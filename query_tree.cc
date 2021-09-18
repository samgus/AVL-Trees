// Sam Gustafsson

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>



using namespace std;

namespace {

// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  string db_line;
  db_line.substr(0, db_line.length() - 2); //reading the line with the two slashes at the end
  string junkLine;
  ifstream myFile (dbx_filename); //reading the file that the user puts through

  for (int i = 0; i < 10; i++){ //skipping the lines that we do not want to read
    getline(myFile, junkLine);
  }
  while (getline(myFile, db_line)){
    stringstream ss(db_line);
    string an_enz_acro = db_line.substr(0, db_line.find('/'));
    string a_rec_seq;

    getline(ss, an_enz_acro, '/'); // getting the acronym and separating it by the /
    while(getline(ss, a_rec_seq, '/')){ // getting the sequence of the acronyms and separating it by the /
      if (a_rec_seq.length() > 0){ //as long as the length is greater than 0, then create a new var "map" of type SequenceMap
        SequenceMap map(a_rec_seq, an_enz_acro);
        a_tree.insert(map); // insert the new map into the tree
      }
    }
  }
string inputLine; //represents the regonition sequence
while(cin >> inputLine){ 
  SequenceMap n(inputLine, " "); //create sequenceMap object with 2 parameters(inputLine, dummy var)
  a_tree.locate(n); //run the find function to locate the acronyms
}


  // Code for running Part 2.1
  // You can use public functions of TreeType. For example:
  // a_tree.insert(10);
  // a_tree.printTree();
}

}  // namespace



int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  cout << "Input filename is " << dbx_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);
  //a_tree.printTree();
  return 0;

}
