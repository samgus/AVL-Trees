#ifndef SEQUENCE_MAP
#define SEQUENCE_MAP

#include <string>
#include <iostream>
#include <vector>

class SequenceMap{
    public:

        //Big Five
        //default constructor
        //this is get called when we create an object of that type
        //ex. SequenceMap value;
        SequenceMap() = default;
        //copy constructor
        //ex. SequenceMap b(&value);
        SequenceMap(const SequenceMap &rhs) = default; //passing in a var of type SequenceMap
        //move contructor
        //ex. SequenceMap c = move(value);
        SequenceMap(SequenceMap &&rhs) = default;
        //copy assignment
        //An assignement assigns a previously created object to something else
        //ex. b = value;
        SequenceMap& operator=(const SequenceMap &rhs) = default;
        //move assignment
        //ex. b = move(value);
        SequenceMap& operator=(SequenceMap &&rhs) = default;

        SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
            enzyme_acronyms_.push_back(an_enz_acro);
            recognition_sequence_ = a_rec_seq;
        }
        //that operates based on the regular string comparison between the 
        //recognition_sequence_ strings (this will be a one line function).
        //ex. SequenceMap c;
        //ex. SequenceMap d;
        //ex. c < d; we would be calling it on c and we're passing in d as the paramater.
        bool operator<(const SequenceMap &rhs) const{
            if (this->recognition_sequence_ < rhs.recognition_sequence_){
                return true;
            }
            return false;
        }
        //Overloading the operator
        //We're printing the indiviual strings of the enzyme vector
        friend std::ostream &operator<<(std::ostream &out, const SequenceMap &map){
            for (int i = 0; i < map.enzyme_acronyms_.size(); i++){
                out << map.enzyme_acronyms_[i] << " ";
            }
            return out;
        }
        //This function assumes that the object’s recognition_sequence_ and 
        //other_sequence.recognition_sequence_ are equal to each other. The 
        //function Merge() merges the other_sequence.enzyme_acronym_ with 
        //the object’s enzyme_acronym_. The other_sequence object will not be affected.
        //ex. SequenceMap e;
        //ex. SequenceMap f;
        //ex. e.Merge(f) calling merge on e with f as the parameter
        void Merge(const SequenceMap &other_sequence){
            for (int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
                this->enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
            }
            
        }
        bool sameRec(const SequenceMap &second) const{ //same renogition
            return (this->recognition_sequence_ == second.recognition_sequence_);
        }

        std::string getSequence(){
            return recognition_sequence_;
        }

    private:
        std::string recognition_sequence_;
        std::vector<std::string> enzyme_acronyms_;

};

#endif