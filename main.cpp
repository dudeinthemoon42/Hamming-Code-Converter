#include <iostream>
#include <iomanip.h>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

/* Written by Bobby Barjasteh

Hamming Code Converter - Prompts for a hexidecimal value (16-bit max length)
--Outputs the corresponding hamming code in hexidecimal
*/

//GLOBALS & FUNCTIONS

int MAX_SIZE = 21; //21-bits is the longest binary string to handle
int wrongbit; //an int used in the hamming checker

//function declarations
void hamming(long &n);
char getHexCharacter(std::string str);
string HexString(string number);
void hammingcheck(string str);
string BinaryString(string number);
string getBinaryCharacter(std::string str);
int getInt(string str); //converts a string to an int, used for the hamming check function


//bools for determining which function to call
bool dohamming = false;
bool docheckhamming = false;
bool dobinary = false;

//bools for use in the hamming code checker only
bool firstparityok,
secondparityok,
fourthparityok,
eigthparityok,
sixteenthparityok = false;

string input = ""; //an input operand used later for input using stringstream class

//global hamming bits - the bits to be determined based on parity
int firsthambit;
int secondhambit;
int fourthhambit;
int eigthhambit;
int sixteenthhambit;

int hamcode; //the new hex code itself

string temphamming; //the temp code to be converted to an int

//MACROS

#define first(arg) (arg & 1)
#define second(arg) (((arg) & (1 << 1)) >> 1)
#define third(arg) (((arg) & (1 << 2)) >> 2)
#define fourth(arg) (((arg) & (1 << 3)) >> 3)
#define fifth(arg) (((arg) & (1 << 4)) >> 4)
#define sixth(arg) (((arg) & (1 << 5)) >> 5)
#define seventh(arg) (((arg) & (1 << 6)) >> 6)
#define eigth(arg) (((arg) & (1 << 7)) >> 7)
#define ninth(arg) (((arg) & (1 << 8)) >> 8)
#define tenth(arg) (((arg) & (1 << 9)) >> 9)
#define eleventh(arg) (((arg) & (1 << 10)) >> 10)
#define twelveth(arg) (((arg) & (1 << 11)) >> 11)
#define thirteenth(arg) (((arg) & (1 << 12)) >> 12)
#define fourteenth(arg) (((arg) & (1 << 13)) >> 13)
#define fifteenth(arg) (((arg) & (1 << 14)) >> 14)
#define sixteenth(arg) (((arg) & (1 << 15)) >> 15)

int main()
{
    cin.setf(ios::hex, ios::basefield);
    cout.setf(ios::hex, ios::basefield);

    long n;

    cout << "Enter 1 for hexidecimal input to convert to the corresponding hamming code hex output." << endl << endl;

    cout << "Enter 2 for hexidecimal input of hamming code to check for errors." << endl << endl;

    cout << "Enter 3 for binary input to hexidecimal output" << endl << endl;

    while(true) //this code checks for a number being entered
    {
        getline(cin, input);

        int mynumber = 0;

        stringstream myStream(input); //this converts a string to a number safely

        if(myStream >> mynumber) //if it's a number
            if(mynumber == 1) //if choice 1
            {
                dohamming = true;
                break;
            }
            if(mynumber == 2)
            {
                docheckhamming = true;
                break;
            }
            if(mynumber == 3)
            {
                dobinary = true;
                break;
            }
        cout << "You entered an invalid entry. Please input a selection: " << endl;
    }

    if(dohamming)
    {
        cout << endl << "Hex input to be converted to hamming code: 0x";
        cin >> n;
        hamming(n); //determines the parity bits
    }

    if(docheckhamming)
    {
        string code = "";

        //want the input and the output to be a standard I/O decimal stream, not in hexidecimal since we are outputting binary
        cin.setf(ios::dec, ios::basefield);
        cout.setf(ios::dec, ios::basefield);

        cout << endl << "Please input a 21-bit (and incorrect) hamming code to be corrected: ";
        getline(cin, code);

        long testnumber;

        //istringstream binStream(code);
        //binStream >> testnumber;

        cout << endl << endl << "You entered: " << code;

        hammingcheck(code); //check the code and output the correct equivalent
    }

    if(dobinary)
    {
        string binary = "";
        cin.setf(ios::dec, ios:: basefield);
        cout.setf(ios::dec, ios::basefield);

        cout << "Binary string: ";
        getline(cin, binary);

        cout << "The string " << binary << "in hexidecimal is: 0x" << HexString(binary) << endl;
    }

    return 0;
}

void hamming(long &n)
{
    int firstcheckbit = ((second(n) + fourth(n) + sixth(n) + eigth(n) + tenth(n) + twelveth(n) + fourteenth(n) + sixteenth(n))); //returns the sum of all the bits checked

    //if the remainder is 0, then we have even parity, and the first parity bit needs to be 0

    int secondcheckbit = ((first(n) + third(n) + fourth(n) + sixth(n) + seventh(n) + tenth(n) + eleventh(n) + thirteenth(n) + fourteenth(n)));

    int fourthcheckbit = ((fifteenth(n) + fourteenth(n) + thirteenth(n) + ninth(n) + eigth(n) + seventh(n) + sixth(n) + second(n) + first(n)));

    int eigthcheckbit = ((twelveth(n) + eleventh(n) + tenth(n) + ninth(n) + eigth(n) + seventh(n) + sixth(n)));

    int sixteenthcheckbit = ((first(n) + second(n) + third(n) + fourth(n) + fifth(n)));

    if((firstcheckbit%2) == 0) //if no remainder
        firsthambit = 0; //parity is even - so make the bit a zero
    else firsthambit = 1; //otherwise correct the odd parity

    if((secondcheckbit%2) == 0)
        secondhambit = 0;
    else secondhambit = 1;

    if((fourthcheckbit%2) == 0)
        fourthhambit = 0;
    else fourthhambit = 1;

    if((eigthcheckbit%2) == 0)
        eigthhambit = 0;
    else if ((eigthcheckbit%2) == 1)
        eigthhambit = 1;

    if((sixteenthcheckbit%2) == 0)
        sixteenthhambit = 0;
    else sixteenthhambit = 1;

    cout << endl << "Number of 1's checked by parity bit 1: " << firstcheckbit << endl;
    cout << "Parity bit 1 is: " << firsthambit << endl << endl;

    cout << "Number of 1's checked by parity bit 2: " << secondcheckbit << endl;
    cout << "Parity bit 2 is: " << secondhambit << endl << endl;

    cout << "Number of 1's checked by parity bit 4: " << fourthcheckbit << endl;
    cout << "Parity bit 4 is: " << fourthhambit << endl << endl;

    cout << "Number of 1's checked by parity bit 8: " << eigthcheckbit << endl;
    cout << "Parity bit 8 is: " << eigthhambit << endl << endl;

    cout << "Number of 1's checked by parity bit 16: " << sixteenthcheckbit << endl;
    cout << "Parity bit 16 is: " << sixteenthhambit << endl << endl;

    string result;
    ostringstream convert;

    convert << std::dec << n; //stores the input in the characters of the stream as hexidecimal value (instead of default dec)

    result = convert.str(); //sets 'result' to the contents of the stream -- result will be whatever the user entered in decimal format

    cout << endl << "The number in decimal is : " << result << endl;

    cout << "From hexidecimal input value 0x"<< n << endl << endl;

    vector<int> final (500);
    final.resize(MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(i == 0)
            final[i] = firsthambit;
        else if(i == 1)
            final[i] = secondhambit;
        else if(i == 3)
            final[i] = fourthhambit;
        else if(i == 7)
            final[i] = eigthhambit;
        else if(i == 15)
            final[i] = sixteenthhambit;
    } //will have to manually assign the bitwise numbers to the vector positions


    //the following are the bitwised-AND values in their corresponding positions in the vector
    //this is how the code would appear if it was spelled out as a 21-bit number
    final[2] = sixteenth(n);
    final[4] = fifteenth(n);
    final[5] = fourteenth(n);
    final[6] = thirteenth(n);
    final[8] = twelveth(n);
    final[9] = eleventh(n);
    final[10] = tenth(n);
    final[11] = ninth(n);
    final[12] = eigth(n);
    final[13] = seventh(n);
    final[14] = sixth(n);
    final[16] = fifth(n);
    final[17] = fourth(n);
    final[18] = third(n);
    final[19] = second(n);
    final[20] = first(n);

    cout << "This number in binary is : ";

    for(int i = 0; i < final.size(); i++) //output the 21-bit code in binary
        cout << final[i] << " ";

    cout << endl << endl;

    //finally, need to calculate the integer value based on the binary it represents
    for(int i = 0; i < final.size(); i++)
        if(final[i] == 1)
            hamcode += (1 * pow(2, (20-i))); //calculating for new hexidecimal code

    cout << endl << "The hamming code for 0x" << n << " in hex is: 0x" << hamcode << endl << endl;

}

std::string HexString(string number)
{
	std::string endresult = "";
	for(int i = 0; i < number.length(); i = i+4)
	{
		endresult += getHexCharacter(number.substr(i,4));
	}
	return endresult;
}


std::string BinaryString(string number)
{
    string endresult = "";
    for(int i = 0; i < number.length(); i++)
    {
        endresult += getBinaryCharacter(number.substr(i,1));
    }
    return endresult;
}

char getHexCharacter(std::string str)
{
    //precondition: must have a string of binary
    //postcondition: returns the hex equivalent as a string

	if(str.compare("1111") == 0) return 'F';
	else if(str.compare("1110") == 0) return 'E';
	else if(str.compare("1101")== 0) return 'D';
	else if(str.compare("1100")== 0) return 'C';
	else if(str.compare("1011")== 0) return 'B';
	else if(str.compare("1010")== 0) return 'A';
	else if(str.compare("1001")== 0) return '9';
	else if(str.compare("1000")== 0) return '8';
	else if(str.compare("0111")== 0) return '7';
	else if(str.compare("0110")== 0) return '6';
	else if(str.compare("0101")== 0) return '5';
	else if(str.compare("0100")== 0) return '4';
	else if(str.compare("0011")== 0) return '3';
	else if(str.compare("0010")== 0) return '2';
	else if(str.compare("0001")== 0) return '1';
	else if(str.compare("0000")== 0) return '0';
	else if(str.compare("111")== 0) return '7';
	else if(str.compare("110")== 0) return '6';
	else if(str.compare("101")== 0) return '5';
	else if(str.compare("100")== 0) return '4';
	else if(str.compare("011")== 0) return '3';
	else if(str.compare("010")== 0) return '2';
	else if(str.compare("001")== 0) return '1';
	else if(str.compare("000")== 0) return '0';
	else if(str.compare("11")== 0) return '3';
	else if(str.compare("10")== 0) return '2';
	else if(str.compare("01")== 0) return '1';
	else if(str.compare("00")== 0) return '0';
	else if(str.compare("1")== 0) return '1';
	else if(str.compare("0")== 0) return '0';
}

string getBinaryCharacter(std::string str)
{
    //precondition: must have a hexidecimal string calling
    //postcondition: returns a string of the binary equivalent

    if(str.compare("0") == 0) return "0000";
    else if(str.compare("1") == 0) return "0001";
    else if(str.compare("2") == 0) return "0010";
    else if(str.compare("3") == 0) return "0011";
    else if(str.compare("4") == 0) return "0100";
    else if(str.compare("5") == 0) return "0101";
    else if(str.compare("6") == 0) return "0110";
    else if(str.compare("7") == 0) return "0111";
    else if(str.compare("8") == 0) return "1000";
    else if(str.compare("9") == 0) return "1001";
    else if((str.compare("A") || str.compare("a")) == 0) return "1010";
    else if((str.compare("B") || str.compare("b")) == 0) return "1011";
    else if((str.compare("C") || str.compare("c")) == 0) return "1100";
    else if((str.compare("D") || str.compare("d")) == 0) return "1101";
    else if((str.compare("E") || str.compare("e")) == 0) return "1110";
    else if((str.compare("F") || str.compare("f")) == 0) return "1111";
}



void hammingcheck (string str)
{
    vector<int> n(500);
    n.resize(MAX_SIZE);

    for(int i = 0; i < str.size(); i++)
    {
        n[i] += getInt(str.substr(i,1)); //our vector gains a converted int from the string str and places it appropriately, creating a vector representing the binary hamming sequence
    }

    if(n[0] == 0) //if 0 in the first position of the vector, aka the first parity bit
        firstparityok = true; //parity is even - eliminating bit 1 as a choice
    else
    {
        firstparityok = false; //otherwise the bits checked by 1 could be wrong
        wrongbit += 1; //the sum of all the parity bits that have odd parity equals the bit that is incorrect in the sequence
    }

    if(n[1] == 0)
        secondparityok = true;
    else
    {
        secondparityok = false;
        wrongbit += 2;
    }

    if(n[3] == 0)
        fourthparityok = true;
    else
    {
        fourthparityok = false;
        wrongbit += 4;
    }

    if(n[7] == 0)
        eigthparityok = true;
    else
    {
        eigthparityok = false;
        wrongbit += 8;
    }

    if(n[15] == 0)
        sixteenthparityok = true;
    else
    {
        sixteenthparityok = false;
        wrongbit += 16;
    }

    if(firstparityok && secondparityok && fourthparityok && eigthparityok && sixteenthparityok)
    {
        cout << endl << endl << "This hamming sequence has correct parity. Therefore, the hamming sequence is also correct.";
        exit(1);
    }

    cout << endl << endl << "The incorrect bit in the sequence is bit number: " << wrongbit << endl;

    cout << "The original hamming sequence in binary is: " << endl;
    for(int i = 0; i < n.size(); i++)
        cout << n[i] << " ";

    cout << endl << endl << "The correct sequence should be: ";

    if(n[wrongbit - 1] == 0) //this changes the value of the incorrect bit in the vector to its opposite
        n[wrongbit - 1]++;
    else n[wrongbit - 1]--;

    for(int i = 0; i < n.size(); i++)
        cout << n[i] << " ";

    cout << endl << endl << "This sequence in hex is: ";

    int newhamminghex;
    for(int i = 0; i < n.size(); i++)
        if(n[i] == 1)
            newhamminghex += (1 * pow(2, (20-i))); //calculating for new hexidecimal code

    cout.setf(ios::hex, ios::basefield);
    cout << newhamminghex << endl << endl;
}

int getInt(string str)
{
    int result;
    istringstream convert(str); //the contents of str, which should be 1 character, are placed into stream

    convert >> result; //result now contains the integer value of whatever was in the string, either a 0 or 1
    return result;
}

