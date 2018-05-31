#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Function declarations  
bool word_check (vector<string> & vector_all_words, vector<string> & vector_good_words, int start_pos, int good_words_counter);
void special_char_removal (vector<string> & vector_good_words);
void selection_sort (vector<string> & vector_good_words);
void remove_dups (vector<string> & vector_good_words);
void print_words (vector<string> & vector_good_words);

int main()
{
	ifstream text_file;
	string word;
	vector<string> vector_all_words ( 1 );                                                       // will contain all of the words read in from text file
	vector<string> vector_good_words ( 1 );  													 // will contain only the words that meet the criteria
	int vector_counter = 0;
	
	text_file.open ("text.txt");
	
	while (text_file >> word)                                                                   // read in entire text file, word-by-word
	{
		vector_all_words[vector_counter] = word;
		vector_counter ++;
		vector_all_words.resize(vector_all_words.size() + 1);                                   // re-size vector per new word 
	}
	
	word_check (vector_all_words,vector_good_words, 1, 0);
	special_char_removal (vector_good_words);
	selection_sort (vector_good_words);
	remove_dups(vector_good_words);
	print_words (vector_good_words);
}

// Function definitions  
  
//#####################################################################  
// bool word_check (vector<string> & vector_all_words,...)
// Purpose: checks for individual words and sequences of words in 
// vector_all_words that meet requirements and adds them to 
// vector_good_words.
// Pre-conditions: vector_all_words is a vector of strings with at least
// one element, start_pos is initiated at 1  
// Post-conditions: vector_good_words will include all words or (if any) 
//  sequences of words that meet requirements
//######################################################################  

bool word_check (vector<string> & vector_all_words, vector<string> &vector_good_words, int start_pos, int good_words_counter)
{
	if ( start_pos<vector_all_words.size() )                                                                                                         // continue for the number of words in vector_all_words (base case)
	{
		bool is_upper = isupper(vector_all_words[start_pos][0]);                                                                                     // starts with an upper-case letter
		bool not_I = vector_all_words[start_pos] != "I";                                                                                             // doesn't start with an I
		bool not_after_period = vector_all_words[start_pos - 1][vector_all_words[start_pos - 1].length() - 1] != '.';                                // its not the first word at beginning of new sentence (i.e. its preceded by a period)
		bool not_after_question = vector_all_words[start_pos - 1][vector_all_words[start_pos - 1].length() - 1] != '?';								 // its not the first word at beginning of new sentence (i.e. its preceded by a question mark)
		
		/* a word after a quotation would need more refinement as there are numerous scenarios */
		//bool not_after_quotation = vector_all_words[start_pos - 1][vector_all_words[start_pos - 1].length() - 1] != '\"';						     // its not the first word at beginning of new sentence (i.e. its preceded by a quotation)
		
		if ( is_upper && not_I && not_after_period && not_after_question) //&& not_after_quotation )      
		{
			vector_good_words[good_words_counter] = vector_all_words[start_pos];                                                                     // if above conditions are met, add the word from the current position of vector_all_words to the current position of vector_good_words
			
			while (true)                                                                                                                             // this loop is looking for sequences of words starting with capital letters
			{
				bool next_word_is_upper = isupper(vector_all_words[start_pos + 1][0]);                                                               // the sequence of words all start with upper-case letters
				bool next_word_is_not_after_period = vector_all_words[start_pos][vector_all_words[start_pos].length() - 1] != '.';                   // the sequence of words cannot be seperated by a period
				bool next_word_is_not_after_question = vector_all_words[start_pos][vector_all_words[start_pos].length() - 1] != '?';				 // the sequence of words cannot be seperated by a question mark
				//bool next_word_is_not_after_quotation = vector_all_words[start_pos][vector_all_words[start_pos].length() - 1] != char(34);		 // the sequence of words cannot be seperated by a quotation 
								
				if ( next_word_is_upper && next_word_is_not_after_period && next_word_is_not_after_question)
				{
				vector_good_words[good_words_counter].append(" " + vector_all_words[start_pos+1]);													 // for as long as the above conditions are met, keep appending words to the current element in vector_good_words
				start_pos = start_pos + 1;																												
				}
				else
				{
				good_words_counter++;																												 
				vector_good_words.resize(vector_good_words.size() + 1);
				break;
				}
			}
		}
	start_pos++;
	word_check (vector_all_words, vector_good_words, start_pos, good_words_counter);                                                                  // recursively call word_check with updated start_pos and good_words_counter
	}
	else
	return 0;
}

//#####################################################################  
// void special_char_removal (vector<string> & vector_good_words)
// Purpose: simply removes special characters (e.g. *, ], ^) that may 
// be located at the end of any strings in vector_good_words.
// Pre-conditions: vector_all_words is a vector of strings with at least
// one element 
// Post-conditions: vector_good_words will not have special characters
// in any of its elements
//######################################################################  

void special_char_removal (vector<string> & vector_good_words)
{
	for (int i = 0; i < vector_good_words.size(); i++)                                                                                                
	{	
	char last_char = vector_good_words[i][ vector_good_words[i].length() - 1 ];
	
	if ( last_char >= 33 && last_char <= 47 )
		vector_good_words[i].erase (vector_good_words[i].length() - 1);
		
	else if ( last_char >= 58 && last_char <= 64 )
		vector_good_words[i].erase (vector_good_words[i].length() - 1);
		
	else if ( last_char >= 91 && last_char <= 96 )
		vector_good_words[i].erase (vector_good_words[i].length() - 1);
		
	else if ( last_char >= 123 && last_char <= 126 )
		vector_good_words[i].erase (vector_good_words[i].length() - 1);
	}	
}

//#####################################################################  
// void selection_sort (vector<string> & vector_good_words) 
// Purpose: sorts vector in ascending order based on ASCII values of 
// its string elements
// Pre-conditions: vector_all_words is a vector of strings with at least
// one element 
// Post-conditions: vector_good_words is sorted in ascending order
//###################################################################### 

void selection_sort (vector<string> & vector_good_words)  								// the selection sort seemed more efficient/interesting to me than the linear sort so I used it instead 
{
	int counter = 0;
	string temp_value;
	int loc_i = 0;
	
	while (counter < vector_good_words.size() )                                         // continue for entire length of vector_good_words                      
	{
		string smallest_value = vector_good_words[counter];
	
		for (int i = counter; i < vector_good_words.size(); i++)                        
		{
			if (vector_good_words[i] < smallest_value)                        		    // repeatedly find the minimum element in vector_good_words and put at the beginning
			{
				smallest_value = vector_good_words[i];
				loc_i = i;
			}
			else
			{
				loc_i = counter;
			}
			
			temp_value = vector_good_words[counter];
			vector_good_words[counter] = smallest_value;
			vector_good_words[loc_i] = temp_value;
		}
		counter ++;
	}
}

//#####################################################################  
// void remove_dups (vector<string> & vector_good_words)
// Purpose: removes any duplicate strings in vector_good_words
// Pre-conditions: vector_all_words is a vector of strings with at least
// one element 
// Post-conditions: vector_good_words no longer has duplicate strings in
// its elements
//###################################################################### 

void remove_dups (vector<string> & vector_good_words)
{
	for (int i = 0; i < vector_good_words.size() - 1; i++)   	                       		// initiate loop starting at 0 through the length of vector_good_words
	{
		while (true)																		// this loop checks for pairs of duplicates and consecutive duplicates (e.g. Trump Is An Idiot, Trump Is An Idiot, Trump Is An Idiot)
		{
			if (vector_good_words[i] == vector_good_words[i + 1] )							
				vector_good_words.erase( vector_good_words.begin() + (i + 1) );             // all consecutive duplicates are deleted, leaving only the original 
			else
				break;																	    // once there are no more duplicates of the current word, break the loop
		}
	}
}

//#####################################################################  
// void print_words (vector<string> & vector_good_words)
// Purpose: simply prints vector_good_words
// Pre-conditions: vector_all_words is a vector of strings with at least
// one element 
// Post-conditions: prints vector_good_words to standard output
//###################################################################### 

void print_words (vector<string> & vector_good_words)
{
	for (int i = 1; i < vector_good_words.size(); i++)                                      
		cout<<vector_good_words[i]<<endl;
}
