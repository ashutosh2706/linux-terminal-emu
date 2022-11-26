#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include<signal.h>
#include<cstdlib>
#include<filesystem>
#include"module"



int get_id(string);
void fun(void);

map<string,int> cmd_map;

int main()
{	
	init_map(cmd_map);
	system("cls");
	col(112);
	cout<<"   Linux Terminal 1.0                                     Welcome                                                       ";
	col(15);
	cout<<"\n\nType 'help' for info\n\n\n";
	string comm;
	while(true) 
	{	
		fun();
		getline(cin,comm);
		if(comm=="") continue;
		vector<string> args;
		string arg = "";
		for(char c:comm) {
			if(c==' ') { args.push_back(arg); arg=""; }
			else arg+=c;
		}
		args.push_back(arg);
		int len = args.size();
		switch(get_id(args[0]))
		{
			case 0:
			for(int cn=1; cn<len; cn++) if(!touch_file(args[cn])) cout<<"Error creating "<<args[cn]<<endl;
			break;
			case 1:
			cout<<current_dir()<<endl;
			break;
			case 2:
			if(len==1) cout<<"Null Argument"<<endl;
			else cat_file(args[1]);
			break;
			
			case 3:
			{
				vector<string> list;
				list = list_files();
				for(string ss:list)
				{
					if(filesystem::is_directory(ss)) 
					{	
						col(144);
						cout<<ss;
						col(15);
						
					}
					else cout<<ss;
					cout<<" ";
				}
				if(!list.empty())
				cout<<endl;
				break;
			}
			case 4:
			disp_help();
			break;
			case 5:
			cout<<"logout\n";
			return 0;
			break;
			case 6:
			system("cls");
			break;
			case 7:
			system("explorer.exe");
			break;
			case 8:
			if(len==1) {
				cout<<"Directory ";
				col(112);
				cout<<".";
				col(15);
				cout<<" not found"<<endl;
			}else 
			change_curr_dir(args[1].c_str());
			break;
			case 9:
			if(len==1) {
				cout<<"Unable to create directory ";
				col(112);
				cout<<".";
				col(15);
				cout<<endl;
			}else
			make_dir(args[1].c_str());
			break;

			default:
			col(192);
			cout<<args[0];
			col(15);
			cout<<" : command not found"<<endl;
		}

	}
	return EXIT_SUCCESS;
	
}


int get_id(string cmd)
{
	if(cmd_map.find(cmd)==cmd_map.end()) return -1;
	else return cmd_map[cmd];
}

void fun()
{	
	string s = current_dir();
	int p = s.find_last_of("\\/");
	col(10);
	cout<<"user@linux-terminal:";
	col(9);
	tilde(s.substr(p+1));
	col(10);
	cout<<"$ ";
	col(15);
}
