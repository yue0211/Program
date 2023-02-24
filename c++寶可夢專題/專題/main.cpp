#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<time.h>
#include"rlutil.h"
#include"Pokemon.h"
using namespace std;
using namespace rlutil;
#define waitkey rlutil::anykey("Press any key to continue...\n")
void draw(char map[][104], string name, GrassPokemon a[], FirePokemon b[], WaterPokemon c[], BugPokemon1 d[]
	, BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], FlyingPokemon2 h[], PoisonPokemon1 s[], 
	ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[]);

void getPokemon(char map[][104],int x,int y, Pokemon* user[],int &PokemonNumber, GrassPokemon a[], int &count, 
	FirePokemon b[], WaterPokemon c[], BugPokemon1 d[], BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], 
	FlyingPokemon2 h[], PoisonPokemon1 s[], ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[]);

void FightwithNPC(Pokemon* user[], char map[][104], int y, int x,int & totalwin,string name);

void Playstart(string &name);

int main( )
{
	GrassPokemon a[3]; FirePokemon b[3]; WaterPokemon c[3]; BugPokemon1 d[3]; BugPokemon2 e[3]; FlyingPokemon1 f[3];
	NormalPokemon g[3]; FlyingPokemon2 h[3]; PoisonPokemon1 s[3]; ElectricPokemon p[3]; GroundPokemon t[3]; PoisonPokemon2 l[3]; PoisonPokemon3 m[3];
	char map[31][104] = {};
	ifstream inFile("yzumap.txt", ios::in);
	if (!inFile)
		std::cout << "File couldn't be opened!\n";
	else
	{
			string name;
			Playstart(name);   //�I�s ��J�ϥΪ̦W�٪��ɮ�
			
			string line;
			int i = 0,k=0;
			while (getline(inFile, line))   // �N�a�ϼg�J map���G���}�C
			{
				for (int j = 0; j < line.size(); j++)
					map[i][j] = line[j];
				i++;
			}

			draw(map,name ,a,b,c,d,e,f,g,h,s,p,t,l,m);   //�I�s�e�a�Ϫ��ɮ�
			
		
	}
	inFile.close();
}
void draw(char map[][104],string name, GrassPokemon a[], FirePokemon b[], WaterPokemon c[], BugPokemon1 d[]
	, BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], FlyingPokemon2 h[], PoisonPokemon1 s[],
	ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[])
{
	int count = 0,totalwin=0,track=0;
	Pokemon* user[3] = {};    // �ΨӦs���a���_�i��
	int PokemonNumber = 0;
	srand(time(0));
	for (int j = 0; j < 31; j++)    // �]�w�����C��
	{
		for (int k = 0; k < 104; k++)
		{
			if (map[j][k] == '~')
				setColor(3);
			else if(map[j][k] == ';')
				setColor(10);
			else if(map[j][k] == '!')
				setColor(12);
			else if(map[j][k] == '#')
				setColor(6);
			else
				setColor(14);
			cout << map[j][k];
		}
		cout << endl;
	}
	locate(20, 30); setColor(4);cout << "@"<<endl;  
	setColor(11);
	locate(5, 33);
	cout << "�ثe���a:" << name;
	locate(5, 35);
	int count2 = 0;
	cout << "�ثe�����_�i�ں���: ";
	for (int i = 0; i < 3; i++)
	{
		if (user[i] == nullptr && count2 == 0)   //�p�G���a�S�_�i�ڡA�h��X�L�A�����ܫh��X�_�i�ڪ��W�r
		{
			cout << "�L\n\n";
			break;
		}
		else if (user[i] == nullptr && count2 != 0)
			break;
		cout << user[i]->getname() << "  ";
		count2++;
	}
	cout << "    �p�G�ݭn�d���_�i�ڸ�T�Ы� r\n\n    �p�G�ݭn����_�i�ڽЫ� t";
	
	int x = 20,y=30; 
	hidecursor();
	saveDefaultColor();
	while (true) 
	{
		if (kbhit()) 
		{
			char k = getch(); 
			locate(x, y);
			if ((map[y - 1][x - 1] == '~' || map[y - 1][x - 1] == ';' || map[y - 1][x - 1] == '#'))  //�i�J��a ���� �٦��J�f ���|�ܦ��ť�
			{
				if(map[y - 1][x - 1] == '~')
					setColor(3);
				else if (map[y - 1][x - 1] == ';')
					setColor(10);
				else if (map[y - 1][x - 1] == '#')
					setColor(6);
				cout << map[y - 1][x - 1];
			}
			else   //��l�ܦ��ť�
			{
				cout << " "; 
			}
			if ((k == 'a' || k == 'A')) --x;       //���ܮy��
			else if ((k == 'd'|| k == 'D')) ++x;
			else if ((k == 'w'|| k == 'W')) --y;
			else if ((k == 's'|| k == 'S')) ++y;
			else if (k == 'r')  //�ϥΪ̿�Jr�ɡA�i�d���_�i��
			{
				setColor(11);
				locate(5, 41);
				cout << "�п�ܷQ�d�ߪ��_�i��(�ѥ��ܥk���_�i�ڤ��O��1 2 3,�п�J1 2 3): ";
				int choice3 = 0;
				cin >> choice3;
				user[choice3 - 1]->printpicture3();
				locate(5, 41);
				cout << "                                                                                                                                        ";
			}
			else if (k == 't')   //�ϥΪ̿�Jt�ɡA�i�R���_�i��
			{
				    setColor(11);
				    locate(5, 41);
					int choice3 = 0;
				   cout << "�п�ܷQ�R�����_�i��(�ѥ��ܥk���_�i�ڤ��O��1 2 3,�п�J1 2 3, ���� : 0 ): ";
				   cin >> choice3;
				   for (int i = 0; i < 2; i++)
				   {
					   if (choice3 == 2)
						   user[1] = user[2];
					   else if (choice3 == 1 && PokemonNumber != 1)
						   user[i] = user[i + 1];
					   else if (choice3 == 3)
						   user[2] = nullptr;
					   else if (choice3 == 1 && PokemonNumber == 1)
						   user[i] = nullptr;
				   }
				   if (choice3 != 0)
				   {
					   user[2] = nullptr;
					   PokemonNumber -= 1;
					   count -= 1;
					   locate(25, 35);
					   cout << "                                                                                                             ";
					   locate(25, 35);
					   for (int i = 0; user[i] != nullptr; i++)
						   cout << user[i]->getname() << "  ";
				   }
				   for (int i = 41; i < 100; i++)
				   {
					   locate(1, i);
					   cout << "                                                                                                                ";
				   }
				   locate(1, 1); cout << " ";
			}
			else if (k == ' ') break;
		
			if ((k == 'a') && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))  //�p�G�O�P�P ��� �Ʀr �h�L�k�q��A�w���Ц�m
				++x;
			else if ((k == 'd' ) && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				--x;
			else if ((k == 'w') && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				++y;
			else if ((k == 's') &&( map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				--y;
			locate(x, y);setColor(4); cout << '@'; 
			int temp = rand() % 10;
			if (temp == 0 && map[y - 1][x - 1] != '#'&&PokemonNumber<3&&(k == 'a'|| k == 'd'|| k == 'w'|| k == 's'))    //10%�����v�i�J���_�y�{�A�Bmap�s���Ȥ���O�ؿv���J�f�A�B�_�i�ڼƶq�n�p�󵥩�3
			{
				setColor(7);
				getPokemon(map,x,y,user, PokemonNumber,a,count,b,c,d,e,f,g,h,s,p,t,l,m);   //�i�J���_�y�{
				PokemonNumber++;
			}
			else if (map[y - 1][x - 1] == '#'&& PokemonNumber==3)
			{
				FightwithNPC(user,map,y,x, totalwin,name);
				if (totalwin == 7)
					exit(0);
				track = 1;
			}
			setColor(11);
			locate(5, 33);
			cout << "�ثe���a:"<<name;
			locate(5, 35);
			int count2 = 0;
			cout << "�ثe�����_�i�ں���: ";
			for (int i = 0; i < 3; i++)   //�p�G���a�S�_�i�ڡA�h��X�L�A�����ܫh��X�_�i�ڪ��W�r
			{
				if (user[i] == nullptr && count2 == 0)
				{
					cout << "�L\n\n";
					break;
				}
				else if (user[i] == nullptr && count2 != 0)
					break;
				cout << user[i]->getname() << "  ";
				count2++;
			}
			if (track == 1)
			{
				locate(5, 41);
				cout << "�ثe��ӳ���: " << totalwin;
			}
			if (PokemonNumber < 3)
			{
				locate(5, 43);
				setColor(12);
				cout << "**�캡�T���_�i��,�~�i�i�J�D�]** ";
			}
		}
	    cout.flush();
		hidecursor();
	}
}
void FightwithNPC(Pokemon* user[], char map[][104],int y,int x, int &totalwin,string name)
{
	system("cls");
	setColor(11);
	int chooce[3] = {};
	Pokemon* replace[3] = {};
	replace[0] = user[0];
	replace[1] = user[1];
	replace[2] = user[2];
	cout << "�Y�N�i�}�P�]�D�����\n\n��Y�@�誺�_�i�ڳ����`�ɡA�������\n\n��Ե�����A���a�_�i�ڱN������_ �C\n\n";

	cout << name << "�{�����_�i�� : " << user[0]->getname() << "  " << user[1]->getname() << "  " << user[2]->getname()<<endl<<endl;

	Pokemon* NPC[3];
	srand(time(0));
	int number = 1 + rand() % 13;

	GrassPokemon a; FirePokemon b; WaterPokemon c; BugPokemon1 d; BugPokemon2 e;
	FlyingPokemon1 f; NormalPokemon g; FlyingPokemon2 h; PoisonPokemon1 k; ElectricPokemon m;
	GroundPokemon n; PoisonPokemon2 o; PoisonPokemon3 p;

	if (number == 1)  //  ��number�ݩ�1~13�ɡA�|�]�wNPC���_�i�ڪ��ݩ�
	{
		NPC[0] = &a; 
		NPC[1] = &c;
		NPC[2] = &e;
	}
	else if (number == 2)
	{
		NPC[0] = &g;
		NPC[1] = &h;
		NPC[2] = &k;
	}
	else if (number == 3)
	{
		NPC[0] = &f;
		NPC[1] = &m;
		NPC[2] = &n;
	}
	else if (number == 4)
	{
		NPC[0] = &b;
		NPC[1] = &d;
		NPC[2] = &p;
	}
	else if (number == 5)
	{
		NPC[0] = &o;
		NPC[1] = &b;
		NPC[2] = &m;
	}
	else if (number == 6)
	{
		NPC[0] = &g;
		NPC[1] = &a;
		NPC[2] = &p;
	}
	else if (number == 7)
	{
		NPC[0] = &b;
		NPC[1] = &g;
		NPC[2] = &h;
	}
	else if (number == 8)
	{
		NPC[0] = &e;
		NPC[1] = &f;
		NPC[2] = &c;
	}
	else if (number == 9)
	{
		NPC[0] = &d;
		NPC[1] = &m;
		NPC[2] = &e;
	}
	else if (number == 10)
	{
		NPC[0] = &e;
		NPC[1] = &k;
		NPC[2] = &n;
	}
	else if (number == 11)
	{
		NPC[0] = &c;
		NPC[1] = &f;
		NPC[2] = &g;
	}
	else if (number == 12)
	{
		NPC[0] = &m;
		NPC[1] = &a;
		NPC[2] = &g;
	}
	else if (number == 13)
	{
		NPC[0] = &k;
		NPC[1] = &b;
		NPC[2] = &f;
	}
	NPC[0]->setData();NPC[0]->choice();NPC[1]->setData();NPC[1]->choice();NPC[2]->setData();NPC[2]->choice();   //�]�wNPC���_�i�ڪ������M�ƭ�


	cout << "�]�D�{�����_�i�� : " << NPC[0]->getname() << "  " << NPC[1]->getname() << "  " << NPC[2]->getname() << "  ";


	setColor(14);
	string solution;
	cout << "\n\n�O�_�ݨ������ ( y or n ) : ";
	while (solution != "n")
	{
		cin >> solution;
		if (solution == "y")
		{
			system("cls");
			for (int j = 0; j < 31; j++)
			{
				for (int k = 0; k < 104; k++)
				{
					if (map[j][k] == '~')
						setColor(3);
					else if (map[j][k] == ';')
						setColor(10);
					else if (map[j][k] == '!')
						setColor(12);
					else if (map[j][k] == '#')
						setColor(6);
					else
						setColor(14);
					cout << map[j][k];
				}
				cout << endl;
			}
			locate(x, y); setColor(4); cout << '@'; 
			locate(5, 37); setColor(11);
			cout << "�p�G�ݭn�d���_�i�ڸ�T�Ы� r\n\n    �p�G�ݭn����_�i�ڽЫ� t";
			return;
		}
		else if (solution == "n")
			break;
		else
			cout << "\n��J���~�A�Э��s��J: ";
	}
	string solution2;
	cout << "\n�O�_�ݬd�� "<< name<<" ���_�i�گ�O ( y or n) : ";
	while (solution2 != "y" || solution2 != "n")
	{
		cin >> solution2;
		if (solution2 == "y" || solution2 == "n")
			break;
		else
		  cout << "\n��J���~�A�Э��s��J: ";
	}
	for (int i = 0; i < 30; i++)
	{
		locate(1, 11 + i);
		cout << "                                                                ";
	}
	int choice3 = -1;
	while (solution2=="y")   // �Ω�d���_�i�گ�O
	{
		setColor(14);
		locate(1,11 );
		cout << "�п�ܷQ�d�ߪ� "<<name<<" ���_�i��(�ѥ��ܥk���_�i�ڤ��O��1 2 3,�п�J1 2 3),�����d��(�п�J4) :  ";
		cin >> choice3;
		while (choice3 <= 0 || choice3 > 4)
		{
			cout<< "\n��J���~�A�Э��s��J: ";
			cin >> choice3;
		}
		if (choice3 == 4)
			break;
		user[choice3 - 1]->printpicture3();
		for (int i = 0; i < 30; i++)
		{
			locate(1, 11 + i);
			cout << "                                                                ";
		}
		locate(1, 11); cout << "                                                                                                                                                                 ";
	}
		for (int i = 0; i < 30; i++)
		{
			locate(1, 11 + i);
			cout << "                                                                                                                                                        ";
		}
		locate(1, 11);
		cout << "�п�� " << name << " ���_�i�ڪ��X������ ( �ѥ��ܥk���O�� 1~3 ),�Ф��O��J3�ӼƦr\n\n";
		for (int i = 0; i < 3; i++)   //�Ω�M�w�_�i�ڪ��X������
		{
			cout << name << " ���� " << i + 1 << " ���_�i�� : ";
			cin >> chooce[i];
			while (chooce[i] <= 0 || chooce[i] >3)
			{
				cout<< "\n��J���~�A�Э��s��J: ";
				cin >> chooce[i];
			}
			cout << endl;
		}
		user[0] = replace[chooce[0] - 1];
		user[1] = replace[chooce[1] - 1];
		user[2] = replace[chooce[2] - 1];
		cout << endl << endl; waitkey;
		
	system("cls");
	 int win = 0,win2=0,cnt=1,track=0,i=0,j=0;

	 while (NPC[2]->getHp()!=0)   // ��NPC���̫�@���_�i�ڪ���q����0��
	 {

		 while (user[i]->getHp() != 0 && NPC[j]->getHp() != 0)  // ��NPC�M���a�ثe�԰����_�i�ڪ���q����0��
		 {
			 user[i]->printpicture();   //�L���a���_�i�ڪ��Ϥ�
			 NPC[j]->printpicture2(); //�LNPC���_�i�ڪ��Ϥ�

			 user[i]->printability2();   //�L���a���_�i�ڪ���O
			 cout << "\n\n"<< name<<" ���Ĥ@���_�i��:" << user[0]->getname() << "\n\n"<<name<<" ���ĤG���_�i��:"
				 << user[1]->getname() << "\n\n"<<name<<" ���ĤT���_�i��:" << user[2]->getname();
			 NPC[j]->printability3(); locate(55, 33);  //�LNPC���_�i�ڪ���O
			 cout << "�]�D���Ĥ@���_�i��:" << NPC[0]->getname(); locate(55, 35);
			 cout << "�]�D���ĤG���_�i��:" << NPC[1]->getname(); locate(55, 37);
			 cout << "�]�D���ĤT���_�i��:" << NPC[2]->getname() << endl << endl << "------------------------------------------------------------------------------\n";

			 cout << "\nRound  " << cnt<<"           ";

			 if (user[i]->getSpeed() >= NPC[j]->getSpeed() && cnt == 1)     //�q�_�i�ڪ��t�קP�_�A���a���_�i�ڥ���A�٬ONPC���_�i�ڥ���
			 {
				 cout << user[i]->getname() << " ������ " << NPC[j]->getname()<< endl ;
				 track = 1;
			 }
			 else if (user[i]->getSpeed() < NPC[j]->getSpeed() && cnt == 1)
				 cout << NPC[j]->getname() << " ������ " << user[i]->getname() << endl;

			 if (track == 1)
			 {
				 cout << "\n\n�]�D�� ";
				 NPC[j]->Fight(user[i]);     //NPC���_�i�ڳQ����  
				 cout <<name<< " �� ";
				 user[i]->Fight(NPC[j]);   //���a���_�i�ڳQ����
			 }
			 else
			 {
				 cout << "\n\n"<<name<<" �� "; 
				user[i]->Fight(NPC[j]);   //���a���_�i�ڳQ����
				 cout << "�]�D�� ";
				 NPC[j]->Fight(user[i]);  // NPC���_�i�ڳQ����  	 
			 }
			 ++cnt;
			  waitkey;
			 system("cls");
			 if (user[i]->getHp() == 0 || NPC[j]->getHp() == 0)//����@�����԰����_�i�ڦ�q��0�ɡA���X�j��
				 break;

		 }
		 if (user[i]->getHp() == 0)  //�p�G�O���a���_�i�ڦ��`�A�h���X���a���U�@���_�i��
		 {
			i += 1;
			win2 += 1;
		 }
		 else if (NPC[j]->getHp() == 0)  //�p�G�ONPC���_�i�ڦ��`�A�h���XNPC���U�@���_�i��
		 {
				j += 1;
				win += 1;
		 }
		 system("cls");
		 track = 0;
		 cnt = 1;
		 if (NPC[2]->getHp() == 0 || user[2]->getHp() == 0)  //�p�GNPC�άO���a�������_�i�ڦ��`�ɡA���X�j��
			 break;
	 }
	 if (win > win2)
	 {
		cout << name<<" ���\n\n";
		totalwin += 1;
		if (totalwin == 7)
		{
			system("cls"); locate(30,20);
			cout << "���� "<<name<<" ����ӹF7���A�w��A���C��!!!";
		}
	 }
	 else if(win < win2)
		 cout << "�]�D���\n\n";
	 if (totalwin != 7)
		 cout << "�ثe "<<name<<" ����ӳ��� : " << totalwin << " ��";
	 cout << endl<<endl; waitkey; 
	 user[0]->originalStatus(); user[1]->originalStatus(); user[2]->originalStatus();   // �N���a���Ҧ��_�i�ڦ^�_��q
	 NPC[0]->originalStatus(); NPC[1]->originalStatus(); NPC[2]->originalStatus(); // �NNPC���Ҧ��_�i�ڦ^�_��q
	 if (totalwin != 7)
	 {
		 system("cls");
		 for (int j = 0; j < 31; j++)
		 {
			 for (int k = 0; k < 104; k++)
			 {
				 if (map[j][k] == '~')
					 setColor(3);
				 else if (map[j][k] == ';')
					 setColor(10);
				 else if (map[j][k] == '!')
					 setColor(12);
				 else if (map[j][k] == '#')
					 setColor(6);
				 else
					 setColor(14);
				 cout << map[j][k];
			 }
			 cout << endl;
		 }
		 locate(x, y); setColor(4); cout << '@'; 
		 locate(5, 37); setColor(11);
		 cout << "�p�G�ݭn�d���_�i�ڸ�T�Ы� r\n\n    �p�G�ݭn����_�i�ڽЫ� t";
	 }
	
}
void getPokemon(char map[][104], int x, int y, Pokemon* user[], int& PokemonNumber, GrassPokemon a[], int& count,
	FirePokemon b[], WaterPokemon c[], BugPokemon1 d[], BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[],
	FlyingPokemon2 h[], PoisonPokemon1 s[], ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[])
{
	char choice ;
	system("cls");
	srand(time(0));
	int  number = 1 + rand() %13;
	int  number2 = 0;
	if (map[y - 1][x - 1] == ';'&& number!=1)  //�p�G�b��a���ҡA�����J���t�_�i�ڪ����v
	{
		number2= 1 + rand() % 9;
		if (number2 == 3)
			number = 1;
	}
	if (map[y - 1][x - 1] == '~' && number != 3)    //�p�G�b�������ҡA�����J����t�_�i�ڪ����v
	{
		number2 = 1 + rand() % 9;
		if (number2 == 3)
			number = 3;
	}
	if (number == 1)     //��number�ݩ�1~13�ɡA�|�Nuser���Ы��V�۹����ݩʪ��_�i��
		user[PokemonNumber] = &a[count];
	else if (number == 2)
		user[PokemonNumber] = &b[count];
	else if (number == 3)
		user[PokemonNumber] = &c[count];
	else if (number == 4)
		user[PokemonNumber] = &d[count];
	else if (number == 5)
		user[PokemonNumber] = &e[count];
	else if (number == 6)
		user[PokemonNumber] = &f[count];
	else if (number == 7)
		user[PokemonNumber] = &g[count];
	else if (number == 8)
		user[PokemonNumber] = &h[count];
	else if (number == 9)
		user[PokemonNumber] = &s[count];
	else if (number == 10)
		user[PokemonNumber] = &p[count];
	else if (number == 11)
		user[PokemonNumber] = &t[count];
	else if (number == 12)
		user[PokemonNumber] = &l[count];
	else if (number == 13)
		user[PokemonNumber] = &m[count];
	count++;
	user[PokemonNumber]->setData();  //�]�w�_�i�ڪ��ƭ�
	user[PokemonNumber]->cleanpicture();  //�M���Ϥ����
	user[PokemonNumber]->choice();   //�]�w�_�i�ڪ�����
	user[PokemonNumber]->printpicture();  //�L�X�_�i�ڪ��Ϲ�
	user[PokemonNumber]->printability();  //�L�X�_�i�ڪ���O
	try
	{
		user[PokemonNumber] ->BeforeCatch();  //���_�e�����ܸܻy
	}
	catch (Pokemon::WrongFail & e)
	{
		cerr << e.what() << endl;
	}
	if (user[PokemonNumber]->getTrack() == 0)   //�p�G�S����_�A�N�N�ϥΪ̦s�_�i�ڹ��������а}�C�]���ū���
	{
		user[PokemonNumber] = nullptr;
		count -= 1;
		PokemonNumber -= 1;
	}
	cout << endl << "�ثe�����_�i�ڼƶq:" << (PokemonNumber + 1) << endl<<endl;

	if ((PokemonNumber + 1) == 3)
		cout << "�w�F�_�i�ڼƶq�����W���A�N�L�k�A�J���_�i��\n\n";
	int count2 = 0;
	cout << "�ثe�����_�i�ں���:";
	for (int i=0;i<3;i++)  //�p�G���a�S�_�i�ڡA�h��X�L�A�����ܫh��X�_�i�ڪ��W�r
	{
		if (user[i] == nullptr && count2 == 0)
		{
			cout << "�L\n\n";
			break;
		}
		else if (user[i] == nullptr && count2 != 0)
			break;
		cout << user[i]->getname() << "  ";
		count2++;
	}
	if ((PokemonNumber + 1) == 3)   //�p�G���a��쪺�_�i�ڼƶq��3���ɡA�h�߰ݪ��a�O�_�ݭn����_�i��
	{
		string choice2;
		int choice3 = 0;
		cout << "\n\n�O�_�ݭn���w�֦����_�i�� ( y or n): ";
		while (cin >> choice2)
		{
			if (choice2 == "n")
				break;
			else if (choice2 =="y")
			{
				cout << "\n�п�ܷQ�R�����_�i��(�ѥ��ܥk���_�i�ڤ��O��1 2 3,�п�J1 2 3, ����:0 ): ";    //��ܻݭn�R�����_�i�ڡA���޿�ܭ��@���_�i�ڡA																																				
				cin >> choice3;																													 //���|�N�̫�@�ӫ��а}�C�]���ū���
				for (int i = 0; i < 2; i++)
				{
					if (choice3 == 2)
						user[1] = user[2];
					else if (choice3 == 1)
						user[i] = user[i + 1];
					else if (choice3 == 3)
						user[2] = nullptr;
				}
				if (choice3 != 0)
				{
					user[2] = nullptr;
					PokemonNumber -= 1;
					count -= 1;
				}
				break;
			}
			else
				cout << "\n\n��J���~�Э��s��J: ";
		}
	}
	cout << endl<<endl;
	waitkey;

	system("cls");
	for (int j = 0; j < 31; j++)   //�N�a�ϦL�X
	{
		for (int k = 0; k < 104; k++)
		{
			if (map[j][k] == '~')
				setColor(3);
			else if (map[j][k] == ';')
				setColor(10);
			else if (map[j][k] == '!')
				setColor(12);
			else if (map[j][k] == '#')
				setColor(6);
			else
				setColor(14);
			cout << map[j][k];
		}
		cout << endl;
	}
	locate(x, y); setColor(4); cout << '@'; 
	locate(5, 37); setColor(11);
	cout << "�p�G�ݭn�d���_�i�ڸ�T�Ы� r\n\n    �p�G�ݭn����_�i�ڽЫ� t";

	return;
}
void Playstart(string& name)  //  ���k���� �� ��J�ϥΪ̦W��
{
	setColor(11);
	cout << " ���k���� : \n\n ��L���� w , a , s , d ���O�������䪺�W�U���k�C\n\n @ : ��ܪ��a���Ҧb��m , * �M ! ���O�����M��� ,���a���i��V�C \n\n"
		<< " # ��ܹD�]�J�f , �i�J��,�N�ߧY�P�D�]�D�i�}��M�C\n\n" << " ���a��i�J�C����,�n���캡3���_�i�ڤ~�i�P�]�D��M�C\n\n" << " �캡3���_�i�ڮ�,�N���|�A�J������_�i��!!!\n\n"
		<< " Ĺ�L���N�]�D7��,�C���~�൲��\n\n";


	cout << endl << endl; waitkey;
	system("cls");
	setColor(10);

	
	char choice;
	cout << "�п�J���a�W��:";
	getline(cin, name);
	cout << "\n���a�W��:" << name<< "\t�O�_�Q��缾�a�W�� ( y or n) :";
	cin >> choice;
	
	while (choice != 'n' )
	{
		if (choice == 'y' )
		{
			cin.ignore();
			name.clear();
			cout << "\n�Ч�缾�a�W��:";
			getline(cin, name);
			cout << "\n���a�W��:" << name << "\t�O�_�Q��缾�a�W�� ( y or n) :";
			cin >> choice;
			cin.ignore();
		}
		else 
		{
			cout << "\n�Э��s��J( y or n):";
			cin >> choice;
			cout << endl;
		}
	}
	system("cls");
}