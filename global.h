#include <iostream>
#include <string>
#include <vector>
#include <bamboo/module/Module.h>
#include <bamboo/module/Class.h>
#include <bamboo/module/Method.h>
#include <bamboo/dcfile/parse.h>
using namespace bamboo;
using namespace std;

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                                "airecv", "broadcast", "ram", "required", "db"};