#include "main.hpp"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) 
{ 
	if (argc < 2)
	{
		cout << "RemoteLink requires at least one argument (path) to use." << endl;

		return EXIT_FAILURE;
	}

	char* localdir_chararr = getenv(localdir_env);
	if (localdir_chararr == NULL)
	{
		localdir_chararr = "/var/www/";
	}
	string localdir_str(localdir_chararr);
	checkTrailingSlash(localdir_str);
//	delete(localdir_chararr);

	char* remotePaths[argc - 1];

	for (int i = 1; i < argc; i++)
	{
		char* path_char = argv[i];
		char* fullPath;

		if (isAbsolutePath(path_char))
		{
			fullPath = path_char;
		}
		else
		{
			fullPath = canonicalize_file_name(path_char);
		}

		string path_str(fullPath);
		string tempStr;

		if (path_str.find(localdir_str) == 0)
		{
			tempStr = path_str.substr(localdir_str.length()).c_str();
			remotePaths[i - 1] = new char[tempStr.size() + 1];
			copy(tempStr.begin(), tempStr.end(), remotePaths[i - 1]);
			
//			delete(&path_str, &tempStr, path_char, fullPath);
		}
		else
		{
			cout << "Invalid path (outside of web server directory ?) : " << path_char << endl;
			throw 2;
		}
	}

	char* hostname_chararr = getenv(hostname_env);
	if (hostname_chararr == NULL)
	{
		hostname_chararr = "http://127.0.0.1/";
	}
	string hostname_str(hostname_chararr);
	checkTrailingSlash(hostname_str);
//	delete(hostname_chararr);


	for (int i = 0; i < argc - 1; i++)
	{
		cout << hostname_str << remotePaths[i] << endl;
	}

	return EXIT_SUCCESS;
}


void checkTrailingSlash(string &path)
{
	if (path.back() != '/')
	{
		path.append("/");
	}
}

bool isAbsolutePath(string& path)
{
	return path[0] == '/';
}
bool isAbsolutePath(char* path)
{
	return path[0] == '/';
}

