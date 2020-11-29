#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>



using namespace std;

const char	localdir_env[] = "RemoteLink_LocalDir",
			hostname_env[] = "RemoteLink_Hostname";

int main(int argc, char* argv[]);

void checkTrailingSlash(string& path);

bool isAbsolutePath(string& path);
bool isAbsolutePath(char* path);