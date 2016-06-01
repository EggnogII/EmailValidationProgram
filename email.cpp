//Programmer: Imran Irfan
//Assignment: TERM PROJECT
//Editor: Notepad
//Compiler: VS 2010 (32-bit)

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//convert to lowercase, necessary first
class toLower {public: char operator()(char C) const {return tolower(C);}};

bool acceptedEmailChar(char C)
{
  //checks if email addresses are valid characters
  bool end;
  if (C >= 'A' && C <= 'Z' || C >= 'a' && C <= 'z' || C >= '0' && C <= '9' || C == '.' || C == '-' || C == '+')
    end = true;
  else
    end = false;

  return end;
} // acceptedEmailChar
 
int main()
{
	 // create an empty list
  const int MAX_EMAIL = 1000; // capacity
  int nEmail = 0; // empty list
  string email[MAX_EMAIL];

  // identifying output statements
 cout << "This program is designed to take the email addresses from an text file and copy them to another text file." << endl;
 cout << "Then it will tell you how many valid email addresses you had from the first " << endl;
 cout << "file." << endl;
 cout << "Note: This program will not print out any duplicate emails." << endl;
 cout << "Email addresses found after the program finishes will be listed and seperated " << endl;
 cout << "with a semicolon, " << endl;
 cout << "and a space on the first line of the output text file." << endl;
 cout << "If you just want to use the default file, then press ENTER." << endl;
  cout << endl;

  string finput;
  string Dinput = "fileContainingEmails.txt";
  string foutput;
  string Doutput = "copyPasteMyEmails.txt";

  cout << "Please enter input filename [DEFAULT: " << Dinput << "]: ";
  getline(cin, finput);

  //If the file input length of characters is anything but 0
  //Then the default file output becomes the file input.
  if (finput.length() != 0)
    Doutput = finput;

  cout << "Please enter output filename [DEFAULT: " << Doutput << "]: ";
  getline(cin, foutput);

  cout << endl;

  //Press Enter for default input, then type name for output.
  //Input becomes default, and output file is specified.
  if (finput.length() == 0 && foutput.length() != 0)
    finput = Dinput;

  //Press Enter for both file input and output prompts and
  //both are the default.
  else if (finput.length() == 0 && foutput.length() == 0)
  {
    finput = Dinput;    
    foutput = Doutput;
  }  

 //If the length of the characters of the first prompt are 
  //anything but 0, and if you press Enter for the prompt
  //for the output, then output becomes input, and vice versa.
  else if (finput.length() != 0 && foutput.length() == 0) 
    foutput = finput;
  
  // open the finput
  ifstream fin;
  fin.open(finput.c_str());
  if (!fin.good()) throw "I/O error";

  // read the input file
  while (true)
  {
    if (!fin.good()) break;

    string linefin;
    getline(fin, linefin);
  
    string theEmail;
    int i;
 
    // traversing the line of text to find '@'
    for (i = 0; i < linefin.length(); i++)
    {
      if (linefin[i] == '@')
      {
        int s = i;
        
        // traverse backwards until an invalid email character found
        while (true)
        {
          s = s - 1;
          if (s < 0) break;
          if (acceptedEmailChar(linefin[s]) == false) break;
        }//while
      
        s = s + 1;
        int e = i;
        bool Dot = false;
       
        //traverse past the '@' until an invalid email character is found
        while (true)
        {
          e = e + 1;
          if (e == linefin.length()) break;   
          if (acceptedEmailChar(linefin[e]) == false) break;
          // to find if it has a dot
          if (linefin[e] == '.')
            Dot = true;
        } // while
        
        // read the valid emails
        bool getDupe = false;
        int count = 0; //add nothing to list if no valid email address
        if (s < i && e > i && Dot == true)
        {
          theEmail = linefin.substr(s, e - s);
          count++;
        } // if

        // skip the duplicate emails
        for (int k = 0; k < nEmail; k++)
        {
          // 2 temporary variables are needed to do case-independent comparisons
          string temp1 = email[k];
          string temp2 = theEmail;

          // transform all letters in finput to lowercase
          transform(temp1.begin(), temp1.end(), temp1.begin(), toLower());
          transform(temp2.begin(), temp2.end(), temp2.begin(), toLower()); 
          // find duplicate by comparison
          if (temp1 == temp2) getDupe = true;
        } // for 
		 
        // skip the duplicate
        if (getDupe == false && nEmail < MAX_EMAIL && count > 0)
          email[nEmail++] = theEmail; //adds value to list
      } // if
    } // for
  } //while

  // close the input file
  fin.close();

  // print valid email addresses found in the input file 
  if (nEmail > 0)
  {
    for (int j = 0; j < nEmail; j++)
      cout << email[j] << endl;
    cout << endl;

    // print the total number of emails
    cout << nEmail << " email addresses were found, and copied to the file, " << foutput << "." << endl;

    cout << endl;
    cout << "NOTE:" << endl;
    cout << "Open the output file , " << foutput << " , copy and paste " << endl;
    cout << "its contents into the 'to, cc, or bcc' field of any email message." << endl;
    cout << "Also note that it is best to use the 'bcc' field as it will protect the privacy" << endl;
	cout << "of the email addresses listed in " << finput << ", by not showing them" << endl;
	cout << "in the message." << endl;

    // write the email addressed were found in the input file to output file
    ofstream fout;
    fout.open(foutput.c_str());
    if (!fout.good()) throw "I/O error";
    for (int p = 0; p < nEmail - 1; p++)
      fout << email[p] << "; ";
    fout << email[nEmail-1] << endl;

    // close the output file
    fout.close();
  } // if

  // there is no any valid email addresses were found or the text file is empty
  else
	  cout << "Sorry, no email addresses were found in the file input.txt" << endl;
  cout << "Press ENTER to end the program." << endl;
  cin.get();

  return 0;
} // main