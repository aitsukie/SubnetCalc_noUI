#include <iostream>
#include <string> //For string
#include <vector> //For vector usage
#include <tuple> //To return more than one variable from a function
#include <algorithm> //For find, can be used without because its vector, but still
#include <iterator> //For distance
using namespace std;

string Introduction()
{
	string sen1 = "\nEach number in an IP adderess is called an octet. ex(1.2.3.4 - 1 is an octet.)\n";
	string sen2 = "Usually IP's are accompanied by a number called CIDR. ex(1.2.3.4/5 - 5 is the CIDR)\n";
	string sen3 = "Therefore, for best usage, please press enter after inputting each octet, and CIDR respectively.\n";
	string str = sen1 + sen2 + sen3;
	return str;
}
void InputVect(vector <int> &v)
{
	

	for (int i = 0; i < v.size(); i++)
	{
		if(i == 0)
		{
			cout << "First  Octet: ";
		}
		else if(i == 1)
			cout << "Second Octet: ";
		else if(i == 2)
			cout << "Third  Octet: ";
		else if(i == 3)
			cout << "Fourth Octet: ";
		else if(i == 4)
			cout << "        CIDR: ";

		cin >> v[i];
	}
}
void OutputVect(vector <int>&v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ".";
	}
	cout << endl;
}
tuple <int,int> setWorking(vector <int> &v, int &cidr)
{
	
	int working = 0; //init
	int prev = 0;
	if (cidr >= 25 && cidr <= 32)
	{
		working = v[3];
		prev = v[2];
		//return working;
	}
	else if (cidr >= 17 && cidr <= 24)
	{
		working = v[2];
		prev = v[1];
	}
	else if (cidr >= 9 && cidr <= 16)
	{
		working = v[1];
		prev = v[0];
	}
	else if (cidr >= 1 && cidr <= 8)
	{
		working = v[0];
	}
	else
	{
		cout << "No in working";
	}

	return make_tuple(working,prev);
}
tuple <int,int> GroupMask(vector <int> &v, int &cidr)
{
	int group = 0; //init
	int mask = 0; //init
	if (cidr == 8 || cidr == 16 || cidr == 24 || cidr == 32)
	{
		group = 1;
		mask = 255;
	}
	else if (cidr == 7 || cidr == 15 || cidr == 23 || cidr == 31)
	{
		group = 2;
		mask = 254;
	}
	else if (cidr == 6 || cidr == 14 || cidr == 22 || cidr == 30)
	{
		group = 4;
		mask = 252;
	}
	else if (cidr == 5 || cidr == 13 || cidr == 21 || cidr == 29)
	{
		group = 8;
		mask = 248;
	}
	else if (cidr == 4 || cidr == 12 || cidr == 20 || cidr == 28)
	{
		group = 16;
		mask = 240;
	}
	else if (cidr == 3 || cidr == 11 || cidr == 19 || cidr == 27)
	{
		group = 32;
		mask = 224;
	}
	else if (cidr == 2 || cidr == 10 || cidr == 18 || cidr == 26)
	{
		group = 64;
		mask = 192;
	}
	else if (cidr == 1 || cidr == 9 || cidr == 17 || cidr == 25)
	{
		group = 128;
		mask = 128;
	}
	else
	{
		cout << "No";
	}

	return make_tuple(group, mask);
}
vector <int> Calculate(vector <int> &v, int &work, int &g)
{
	int i = 0;
	int curr = 0;

	while(curr <= work) //While current is less than the working octet
	{
		i++;
		curr = i * g; //Current = index multiplied by group size
		v.push_back(curr);
	}

	return v;
}
int DetermineNID(vector <int> &v, int &wrk_octet)
{
	//Find working octet in the ID_NEXT vector
	auto OctetIn = find(v.begin(), v.end(), wrk_octet) != v.end();
	int NID = 0; //Initialize network ID to 0

	if(OctetIn) //If true
	{
		NID = wrk_octet;
	}
	else if(v.size() > 1)
	{
		NID = v.rbegin()[1]; // Second last element in ID_NEXT;
	}

	return NID;
}
int DetermineNEXT(vector <int> &idnext, vector <int> &IPvec, int &wrk_octet, int &frst, int &prev)
{
	int NextNet = 0; //Initialize next net to 0
	int last = idnext.back();//Last element in the ID_NEXT vector

	if(wrk_octet != frst && last == 256) //If the working octet is not the first and next net reaches 256, set it to 0
	{

		NextNet = 0;

	}
	//else if(wrk_octet == frst && last == 256)
	//{
	//	/*If the working octet is the first one, and the last element in ID_NEXT is 256,
	//	Then the next network is N/A. There is no such thing*/
	//	NextNet = 0;
	//}
	else//Otherwise the NextNetwork is the last element of ID_NEXT
	{
		NextNet = last;
	}

	return NextNet;

}
void DisplayFirst(int &num, string &word)
{
	cout << num << '.' << word << endl;
}
void DisplaySecond(int& ip_octet, int &num, string& word)
{
	cout << ip_octet << '.' << num <<  '.' << word << endl;
}
void DisplayThird(int& ip_octet, int& ip_octet2, int &num, string& word)
{
	cout << ip_octet << '.' << ip_octet2 << '.' << num << '.' << word << endl;
}
void DisplayFourth(int &ip_octet, int &ip_octet2, int &ip_octet3, int &num)
{
	cout << ip_octet << '.' << ip_octet2 << '.' << ip_octet3 << '.' << num << endl;
}
void FancyNext(int &octet_before, int &frst, int &scnd, int &thrd, int &frth, int &NextNet, string &NNS, int &wrk_octet )
{

	if (NextNet == 0)
	{
		octet_before = octet_before + 1;
	}
	else
	{
		octet_before = octet_before;
	}
	if (wrk_octet == frst)
	{
		if(NextNet == 256)
		{
			cout << "Next Network not Available." << endl;
		}
		else
		{
			DisplayFirst(NextNet, NNS);

		}
	}
	if (wrk_octet == scnd)
	{
		DisplaySecond(frst, NextNet, NNS);
	}

	if (wrk_octet == thrd)
	{
		DisplayThird(frst, scnd, NextNet, NNS);
	}

	if (wrk_octet == frth)
	{
		DisplayFourth(frst, scnd, thrd, NextNet);
	}

	if (NextNet == 0)
	{
		octet_before = octet_before - 1;
	}
	else
	{
		octet_before = octet_before;
	}

}
void Details(int& work, int& NID, int& NextNet, int& frst, int& scnd, int& thrd, int& frth, int &mask)
{
	int BIP = NextNet - 1;
	int LIP = BIP - 1;
	int FIP = NID + 1;
	

	if(NextNet == 0 || NextNet ==256) //works for 4,3,2
	{
		BIP = 255;
		LIP = 254;
	}
	string NNS;
	string BRD;
	string LAST;
	string FRST;
	int max_subnet = 255;



	string ID   =    "Network ID:      ";
	string NextIP =  "Next Network IP: ";
	string brdIP =   "Broadcast IP:    ";
	string lastIP =  "Last Host IP:    ";
	string firstIP = "First Host IP:   ";
	string submask = "Subnet Mask:     ";




	if (work == frst)
	{
		NNS = "0.0.0";//NID,NEXT NET AND SUNET
		BRD = "255.255.255";
		LAST = "255.255.254";
		FRST = "0.0.1";

		cout << ID;
		DisplayFirst(NID,NNS);

		cout << NextIP;
	//	DisplayFirst(NextNet, NNS);
		int fill = 0; //filler intger, no octet to be worked on
		FancyNext(fill, frst, scnd, thrd, frth, NextNet, NNS, work);

		cout << brdIP;
		DisplayFirst(BIP, BRD);
		cout << lastIP;
		DisplayFirst(BIP, LAST);
		cout << firstIP;
		DisplayFirst(NID, FRST);
		cout << submask;
		DisplayFirst(mask, NNS);

	}

	if (work == scnd)
	{
		NNS = "0.0";//NID,NEXT NET AND SUNET
		BRD = "255.255";
		LAST = "255.254";
		FRST = "0.1";

		cout << ID;
		DisplaySecond(frst,NID, NNS);
		cout << NextIP;
		
		FancyNext(frst, frst, scnd, thrd, frth, NextNet, NNS, work);


		cout << brdIP;
		DisplaySecond(frst, BIP, BRD);
		cout << lastIP;
		DisplaySecond(frst, BIP, LAST);
		cout << firstIP;
		DisplaySecond(frst, NID, FRST);
		cout << submask;
		DisplaySecond(max_subnet, mask, NNS);


	}

	if (work ==thrd)
	{
		NNS = "0";//NID,NEXT NET AND SUNET
		BRD = "255";
		LAST = "254";
		FRST = "1";

		cout << ID;
		DisplayThird(frst,scnd, NID, NNS);
		cout << NextIP;

		FancyNext(scnd, frst, scnd, thrd, frth, NextNet, NNS, work);

		cout << brdIP;

		DisplayThird(frst, scnd, BIP, BRD);
		cout << lastIP;

		DisplayThird(frst, scnd, BIP, LAST);
		cout << firstIP;

		DisplayThird(frst, scnd, NID, FRST);
		cout << submask;
		DisplayThird(max_subnet, max_subnet, mask, NNS);
	}

	if (work == frth)
	{
		cout << ID;
		DisplayFourth(frst,scnd,thrd,NID);

		cout << NextIP;	
		FancyNext(thrd, frst, scnd, thrd, frth, NextNet, NNS, work);
		cout << brdIP;
		DisplayFourth(frst, scnd, thrd, BIP);
		cout << lastIP;
		DisplayFourth(frst, scnd, thrd, LIP);
		cout << firstIP;
		DisplayFourth(frst, scnd, thrd, FIP);
		cout << submask;
		DisplayFourth(max_subnet, max_subnet, max_subnet, mask);


	
		

	}

	
}
int main()
{

	string intro = Introduction(); //Brief Explanation of concept and usage.
	cout << intro << endl; //Outputing text

	vector <int> IP_CIDR(5,0); //Initializing vector with 0's.
	InputVect(IP_CIDR);
	int frst = IP_CIDR[0]; //first octet at the 0th element of vector. 
	int scnd = IP_CIDR[1]; //second octet
	int thrd = IP_CIDR[2]; //Third octet
	int frth = IP_CIDR[3]; //Fourth octet
	int cidr = IP_CIDR[4]; //CIDR

	//Set-up 
	 
	//For determining which octet to work on based on CIDR
	//int working_octet = setWorking(IP_CIDR, cidr);
	tuple <int, int> workpev = setWorking(IP_CIDR, cidr);
	int working_octet = get<0>(workpev);
	int prev_octet = get<1>(workpev);

	//Determine group size and subnet mask based on CIDR
	tuple <int, int> extractGroup = GroupMask(IP_CIDR, cidr); 
	int group_size = get<0>(extractGroup); //extract the group size

	//Vector to store the potential NetworkID and NextNetwork
	vector <int> ID_NEXT;

	//Calculate potential values
	Calculate(ID_NEXT, working_octet, group_size);

	//Determine the NetID from the ID_NEXT vector
	int NetworkID = DetermineNID(ID_NEXT, working_octet);

	//Determine the NextNetwork from the ID_Next
	int NextNetwork = DetermineNEXT(ID_NEXT, IP_CIDR, working_octet, frst, prev_octet);

	int mask = get<1>(extractGroup);//ExtractSubnetMask
	cout << endl;
	Details(working_octet, NetworkID, NextNetwork, frst, scnd, thrd, frth, mask);

	return 0;
}