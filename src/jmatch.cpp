#include "jmatch.h"

namespace jaffe{
	bool matchString(const string line, const string key, string* s){
		string str_temp = line;
		if(line.find(key) == string::npos) {
			return false;
		}
		str_temp = line.substr(key.length(), line.length() - key.length());

		int m = 0, n = 0;
		if(str_temp.find_first_of("\"") == string::npos){
			return false;
		}
		m = str_temp.find_first_of("\"");
		if(str_temp.find_last_of("\"") == string::npos){
			return false;
		}
		n = str_temp.find_last_of("\"");
		*s = str_temp.substr(m + 1, n - m - 1);
		return true;
	}

	bool matchInt(const string line, const string key, int *i){
		string str_temp = line;
		if(line.find(key) == string::npos){
			return false;
		}
		str_temp = line.substr(key.length(), line.length() - key.length());

		stringstream ss;
		ss << str_temp;
		ss >> *i;
		return true;
	}

	bool matchFloat(const string line, const string key, float* f){
		string str_temp = line;
		if(line.find(key) == string::npos){
			return false;
		}
		str_temp = line.substr(key.length(), line.length() - key.length());

		stringstream ss;
		ss << str_temp;
		ss >> *f;
		return true;
	}

	bool matchBool(const string line, const string key, bool* b){
		if (line.find("true") != string::npos){
			*b = true;
			return true;
		}
		*b = false;
		return false;
	}

	bool matchDouble(const string line, const string key, double* d){
		string str_temp = line;
		if(line.find(key) == string::npos){
			return false;
		}
		str_temp = line.substr(key.length(), line.length() - key.length());

		stringstream ss;
		ss << str_temp;
		ss >> *d;
		return false;
	}

	bool matchLong(const string line, const string key, long *l){
		string str_temp = line;
		if(line.find(key) == string::npos){
			return false;
		}
		str_temp = line.substr(key.length(), line.length() - key.length());

		stringstream ss;
		ss << str_temp;
		ss >> *l;
		return false;
	}

} // namespace jaffe