# String Analysis

This algorithm initially reads a text file (text.txt) into a vector, with each word stored as a separate element in the vector. Each word in this vector is analyzed to determine:

1. If it starts with an upper-case letter
2. Is not at the beginning of a sentence
    - Not following a period or question mark
    - Quotation marks may also mark the end of a sentence but are not currently considered 
1. If a word meets the above criteria, it is then further analyzed to check if it’s in a longer sequence of words that meet the above criteria (e.g. “Hello World, Hello Word”) 
 - If so, the entire sequence of words is stored as a single element in a vector 
 - If not, just the individual word is stored in a vector

Next, the entire vector is sorted in ascending order, special characters (e.g. *, @, ^) at the end of any word are removed, and duplicates are eliminated.  

[![stringanalysis](http://206.189.195.136/wp-content/uploads/2018/05/Stringanalysis.jpg "stringanalysis")](http://206.189.195.136/wp-content/uploads/2018/05/Stringanalysis.jpg "stringanalysis")
