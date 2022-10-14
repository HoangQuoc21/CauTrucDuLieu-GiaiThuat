#include <iostream>    // stream I/O
#include <fstream>
#include <string>      // string
#include <cassert>     // assert()
using namespace std;

char CaesarEncode(char ch, int key);

// Question 1. Write a function returns the position of the key, if the key does not exist, returns -1
int LinearSearch(int* a, int n, int key) {
  for (int i = 0; i < n; i++)
    if (a[i] == key)
      return i;
  return -1;
}

// Question 2. Write a function prints the binary form of the positive integer n
void PrintBinary(int n){
  if (n == 0)
    return;
  PrintBinary(n/2);
  cout << n%2;
}

//  Question 3. 
bool encode_message(){
  // 0. Display introductory message 
  cout << "\nThis program uses the Caesar cipher to encode the contents of a"
       << "\nfile and writes the encoded characters to another file.\n";
  
  // 1. (0.25 point) Open inFile for reading 
  string inputFile = "message.txt";
  ifstream fin;
  fin.open(inputFile);

  // 2. (0.25 point) If file is failed to open, display an error message and return False; otherwise, display success message
  if(!fin.is_open()){
  	cout<<" Fail to open " << inputFile << " to read.\n";
  	return false;
  }
  else
    cout << "Successfully open " << inputFile << " to read.\n";
  
  // 3. (0.25 point) Open outFile for output.
  string outputFile = "output.txt";
  ofstream fout;
  fout.open(outputFile);

  // 4. (0.25 point) If file is failed to open, display an error message and return False; otherwise, display success message
  if(!fout.is_open()){
  	cout<<"Fail to open " << outputFile << " to write.\n";
  	return false;
  }
  else
    cout << "Successfully open " << outputFile << " to write.";
    
  // 5. (3.0 point) Read the content of inFile and encode the message then write the encoded message to outFile 
  string line;
  while(getline(fin, line, '\0')){
    for (int i = 0; i < line.length(); i++)
      fout << CaesarEncode(line[i], 5);
  }
  // 6. (0.5 point) close the connection to the input and output file
  fin.close();
  fout.close();

  // 7. display a 'successful completion' message
  cout << "\nProcessing complete.\nEncoded message is in "  << outputFile << endl;
  return true;
}

int main()
{
  int n = 6;
  int *a = new int[n]{1,2,3,4,5,0};
  int key = 0;

  int pos = LinearSearch(a, 6, 0);
  cout << "\nVi tri cua " << key << " trong mang la: " << pos << endl;

  // uncomment this block to run question 2
  cout << "Dang nhi phan cua " << n << " la: ";
  PrintBinary(n);
  cout << "\n";
  
  encode_message(); // uncomment this line to run question 3

  return 1;
}

/*============================================================
 * CaesarEncode implements the Caesar cipher encoding scheme.        
 *                                                                    
 * Receive: ch, a character.                                         
 *          key, the amount by which to rotate ch.                   
 * Return:  The character that is key positions after ch,            
*/

#include <cctype>      // isupper(), islower()

char CaesarEncode(char ch, int key)
{
  const int FIRST_UPPER = 65,
            FIRST_LOWER = 97,
            NUM_CHARS = 26;

  if (key <= 0 || key >= NUM_CHARS)
    {
      cerr << "\n*** CaesarEncode: key must be between 1 and 25\n" << endl;
      exit(1);
    }
  
  if (isupper(ch))
    return (ch - FIRST_UPPER + key) % NUM_CHARS + FIRST_UPPER;
  else if (islower(ch))
    return (ch - FIRST_LOWER + key) % NUM_CHARS + FIRST_LOWER;
  else
    return ch;
}


