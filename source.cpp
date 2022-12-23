#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include<dirent.h>
#include<unistd.h>
#include<signal.h>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cstring>
#include<filesystem>
#include"module.h"

string get_full_name(vector<string>& args)
{
	string name = "";
	for(int i = 1; i < args.size(); i++) 
	{
		if(i != args.size() - 1) { name+=args[i]; name+=" "; }
		else name+=args[i];
	}
	return name;
}

void log_err(string e, string msg)
{
	col(192);
	cout << e;
	col(15);
	cout << " : ";
	cout << msg << endl;
}

int main()
{	
	init_command_map(cmd_map);
	system("cls");
	col(112);
	cout<<"   Linux Terminal                                         Welcome                                                       ";
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
		switch(get_command_id(args[0]))
		{
			case 0:
			for(int cn=1; cn<len; cn++) if(!touch_file(args[cn])) cout<<"Error creating "<<args[cn]<<endl;
			break;

			case 1:
			cout<<current_dir()<<endl;
			break;

			case 2:
			if(len==1) log_err(args[0], "Missing operand");
			else cat_read(get_full_name(args));
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
					cout<<"  ";
				}
				if(!list.empty())
				cout<<endl;
			}
			break;

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
			if(len==1) log_err(args[0], "Missing operand");
			else 
			{
				change_curr_dir(get_full_name(args).c_str());
			}
			break;


			case 9:
			if(len==1) log_err(args[0], "Missing operand");
			else make_dir(get_full_name(args).c_str());
			break;

			case 10:
			if(len == 1) log_err(args[0], "Missing operand");
			else rm_file(get_full_name(args));
			break;

			case 11:
			if(len == 1) log_err(args[0], "Missing operand");
			else rm_dir(get_full_name(args));
			break;

			case 12:
			if(len < 3) log_err(args[0], "Missing operand");
			else 
			{
				vector<string> v;
				for(int i = 1; i < len; i++) v.emplace_back(args[i]);
				move(v);
			}
			break;

			case 13:
			if(len == 1) _DATE("");
			else _DATE(args[1]);
			break;

			case 14:
			log_err(args[0], "Missing operand");
			break;

			default:
			if(args[0].find("cat>") != string::npos) cat_write(args[0]);
			else
			{
				col(192);
				cout<<args[0];
				col(15);
				cout<<" : command not found"<<endl;
			}
		}

	}
	return EXIT_SUCCESS;
	
}


int get_command_id(string cmd)
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
	dir_tree(s.substr(p+1));
	col(10);
	cout<<"$ ";
	col(15);
}