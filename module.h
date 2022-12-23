using namespace std;

string current_dir(void);
vector<string> list_files(void);
bool touch_file(string);
void init_map();

#define col(b) SetConsoleTextAttribute(h,b)
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
string home_dir = "";

void fun(void);
int get_command_id(string);
map<string,int> cmd_map;

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
	cout<<"touch";
	col(15);
	cout<<" ";
	col(160);
	cout<<"pwd";
	col(15);
	cout<<" ";
	col(160);
	cout<<"cat";
	col(15);
	cout<<" ";
	col(160);
	cout<<"ls";
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
	cout<<"rm";
	col(15);
	cout<<" ";
	col(160);
	cout<<"rmdir";
	col(15);
	cout<<" ";
	col(160);
	cout<<"mv";
	col(15);
	cout<<" ";
	col(160);
	cout<<"date";
	col(15);
	cout<<" ";
	col(160);
	cout<<"nautilus";
	col(15);
	cout << " ";
	col(160);
	cout << "clear";
	col(15);
	cout << " ";
	col(160);
	cout << "exit";
	col(15);
	cout << endl;
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
		cout<<"Error creating directory ";
		col(112);
		cout<<name;
		col(15);
		cout << " " << endl;
	}
}

void cat_read(string __fname)
{	

	ifstream infile; // Declare input file stream
	infile.open(__fname); // Open file for reading
	if(!infile.good())		// Check if file exists and is readable
	{
		cout << "File ";
		col(112);
		cout << __fname;
		col(15);
		cout << " not found or is not readable" << endl;
		return;

	}
	string line;
	while (std::getline(infile, line)) 	// Read a line from the file
	{
    	cout << line << endl; // Print the line to the console
  	}

  	infile.close();

}

void cat_write(string arg)
{	
	string file = arg.substr(4), input;
	ofstream output_file;
	output_file.open(file);
	while(getline(cin, input) && input != "\0")
	{
		output_file << input << endl;
	}
	output_file.close();
}

void rm_file(string file_name)
{
	if(filesystem::is_directory(file_name))
	{
		cout << "Cannot remove ";
		col(112);
		cout << file_name;
		col(15);
		cout << " : Is a directory" << endl;
		return;
	}
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
		cout << "filesystem error";
		col(15);
		cout << " : " << err.what() << endl;
	}
}

void delete_dir(const char* dir_name)
{
	DIR* dir = opendir(dir_name);
  	if (dir == nullptr) return;
	dirent* entry;
	while ((entry = readdir(dir)) != nullptr)
  	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

    	string path = string(dir_name) + "/" + entry->d_name;
    	if (entry->d_type == DT_DIR)
    	{
      		// Recursively delete subdirectory
      		delete_dir(path.c_str());
		rmdir(path.c_str());
    	}
    	else
    	{
      		// If file found then delete file
      		int result = unlink(path.c_str());
      		if (result != 0)
      		{
        		cout << "Error deleting file" << endl;
      		}
    	}
  	}
	closedir(dir);
}

void rm_dir(string dir_name)
{
	if(!filesystem::is_directory(dir_name))
	{
		cout << "Failed to remove ";
		col(112);
		cout << dir_name;
		col(15);
		cout << " : Not a directory" << endl;
	}else
	{
		delete_dir(dir_name.c_str());
		int result = rmdir(dir_name.c_str());
  		if (result != 0)
  		{
			cout << "Directory ";
			col(112);
			cout << dir_name;
			col(15);
			cout << " not removed" << endl;
  		}
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

void move(vector<string>& files)
{	
	/*  Moving file from one folder to another can be cleverly done using rename(old_name, new_name) method
		We can pass the new name for file with a prefix string containing "/" concatenated with existing file name
		Function will treat prefix string before "/" as folder and moves the file into that folder.
		As we know file "tmp/new.txt" shows that "new.txt" file is inside "tmp" folder. This follows exactly same thing
	*/
	string dest = files.back();							// For moving multiple files, we store them in an array, and iterate over that array to move them one by one
	for(int i = 0; i < files.size() - 1; i++)			// Last entry is the destination itself, so iterate from start -> size-1
	{	
		string dir = dest + "/" + files[i];
		if(rename(files[i].c_str(), dir.c_str()))
		{
			cout << "File ";
			col(112);
			cout << files[i];
			col(15);
			cout << " not moved" << endl;
		}
	}
}