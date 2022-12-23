using namespace std;

string current_dir(void);
vector<string> list_files(void);
bool touch_file(string);
void init_map();

#define col(b) SetConsoleTextAttribute(h,b)
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
string home_dir = "";

void init_command_map(map<string,int>& cmd)
{	
	vector<string> commands = { "touch", "pwd", "cat", "ls", "help", "exit", "clear", "nautilus", "cd", "mkdir", "rm", "rmdir", "mv", "date", "cat>" };
	for(int i=0; i<commands.size(); cmd[commands[i]]=i, i++);
}

string current_dir() 
{
	return filesystem::current_path().string();
}

void disp_help()
{
	cout<<"Supported Commands: ";
	col(160);
	cout<<"cat";
	col(15);
	cout<<" ";
	col(160);
	cout<<"touch";
	col(15);
	cout<<" ";
	col(160);
	cout<<"pwd";
	col(15);
	cout<<" ";
	col(160);
	cout<<"ls";
	col(15);
	cout<<" ";
	col(160);
	cout<<"clear";
	col(15);
	cout<<" ";
	col(160);
	cout<<"cd";
	col(15);
	cout<<" ";
	col(160);
	cout<<"mkdir";
	col(15);
	cout<<" ";
	col(160);
	cout<<"nautilus";
	col(15);
	cout<<" ";
	col(160);
	cout<<"exit\n";
	col(15);
}

void dir_tree(string t)
{

	if(home_dir=="" || home_dir == t)
	{
		home_dir = t;
		cout<<"~";
	}
	else cout << "~/" << t;
	
}

vector<string> list_files()
{
	vector<string> list;
	for (const auto & entry : filesystem::directory_iterator(current_dir()))
        {	
		filesystem::path p = entry.path();
		string pth = p.string();
		int index = pth.find_last_of("\\/");
		list.push_back(pth.substr(index+1));
	}
	return list;
	
}

bool touch_file(string name)
{

	fstream file;
	file.open(name, ios::out);
	if(!file) return 0;
	return 1;
}

void change_curr_dir(const char* dir)
{
	if(chdir(dir))
	{
		cout<<"Directory ";
		col(112);
		cout<<dir;
		col(15);
		cout<<" not found"<<endl;
	}
}
	
void make_dir(const char* name)
{
	if(mkdir(name)==-1)
	{
		cout<<"Error creating directory\n";
	}
}

void cat_read(string __fname)
{	
	ifstream f(__fname);
	if(!(f.get(), f.eof()))
	{
		if(f.is_open()) 
		{
			cout<<f.rdbuf();
			cout<<endl;
		}
		else cout<<"'"<<__fname<<"' doesn't exist!"<<endl;
	}
}

void rm_file(string file_name)
{
	try 
	{
		if(!(filesystem::remove(file_name)))
		{
			cout << "File ";
			col(112);
			cout << file_name;
			col(15);
			cout << " not found" << endl;
		}
	}
	catch(const filesystem::filesystem_error& err) 
	{
		col(192);
		cout << "FileSystem Error:";
		col(15);
		cout << " " << err.what() << endl;
	}
}

void _DATE(string arg)
{
	time_t now;
	
	if(arg == "")
	{
		// current date/time based on current system
   		now = time(0);
		char* dt = ctime(&now);
		cout << dt;
	}else if(arg == "+%A")
	{
		now = time(nullptr);
		tm *localTime = localtime(&now);

    	// Get the day of the week (0-6, with 0 being Sunday)
    	int dayOfWeek = localTime->tm_wday;

    	// Display the day of the week as a string
		switch (dayOfWeek) {
			case 0:
				cout << "Sunday" << endl;
				break;
			case 1:
				cout << "Monday" << endl;
				break;
			case 2:
				cout << "Tuesday" << endl;
				break;
			case 3:
				cout << "Wednesday" << endl;
				break;
			case 4:
				cout << "Thursday" << endl;
				break;
			case 5:
				cout << "Friday" << endl;
				break;
			case 6:
				cout << "Saturday" << endl;
				break;
			default:
				cout << "Invalid day of week";
				break;
		}
	}else if(arg == "+%a")
	{
		string day;
		now = time(nullptr);
		tm *localTime = localtime(&now);
    	int dayOfWeek = localTime->tm_wday;
		switch (dayOfWeek) {
			case 0:
				cout << "Sun" << endl;
				break;
			case 1:
				cout << "Mon" << endl;
				break;
			case 2:
				cout << "Tue" << endl;
				break;
			case 3:
				cout << "Wed" << endl;
				break;
			case 4:
				cout << "Thu" << endl;
				break;
			case 5:
				cout << "Fri" << endl;
				break;
			case 6:
				cout << "Sat" << endl;
				break;
			default:
				cout << "Invalid day of week";
				break;
		}

	}else cout << "Invalid date operand" << endl;

}

void cat_write()
{
	
}