#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"

using namespace std;

/* Check:
 * https://github.com/jbeder/yaml-cpp/wiki/Tutorial
 * https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML
 */

int main()
{
	YAML::Node config = YAML::LoadFile("pikachu.yaml");

	/* YAML read example */
	try {
		cout << "name: " << config["name"].as<string>() << endl;
		cout << "age: " << config["age"].as<int>() << endl;

		/* a not exist item, use try-catch to prevent the failure */
		cout << "a not exist yaml item: " << config["christmas tree"].as<string>() << endl;
	} catch(...) {
		cout << "christmas tree is not exist." << endl;
	}

	cout << endl;

	/* yaml write example */
	YAML::Emitter out;

	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << "Drumpf";
	out << YAML::Key << "age";
	out << YAML::Value << 69;

	std::cout << "Export yaml\n" << out.c_str(); //Print yaml on screen

	/* Save yaml into file */
	char filename[] = "merica.yaml";

	fstream fp;
	fp.open(filename, ios::out);

	if(fp != 0) {
		fp << out.c_str() << endl; //Write yaml
	}

	return 0;
}
