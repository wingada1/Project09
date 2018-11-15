#include "proj09_bimap.h"
#include<algorithm>
using std::lower_bound; using std::find_if;

vector<pair<string, string>>::iterator BiMap::find_key(string key) {
	vector<pair<string, string>>::iterator itr;
	itr = lower_bound(ordered_by_keys_.begin(), ordered_by_keys_.end(), key,
		[](std::pair<string, string> const & x, string d)
	{ return x.first < d; });
	return itr;
}

vector<pair<string, string>>::iterator BiMap::find_value(string value) {
	vector<pair<string, string>>::iterator itr;
	itr = lower_bound(ordered_by_vals_.begin(), ordered_by_vals_.end(), value,
		[](std::pair<string, string> const & x, string d)
	{ return x.second < d; });
	return itr;
}

BiMap::BiMap(initializer_list<pair<string, string>> v) {
	vector<pair<string, string>> vect;
	vect = v;
	string str1, str2;
	for (auto i = 0; i < vect.size(); i++) {
		str1 = vect[i].first;
		str2 = vect[i].second;
		add(str1, str2);
	}
}

size_t BiMap::size() {
	size_t r = ordered_by_keys_.size();
	return r;
}

string BiMap::value_from_key(string s) {
	for (auto i = 0; i < ordered_by_keys_.size(); i++) {
		if (s == ordered_by_keys_[i].first)
			return ordered_by_keys_[i].second;
	}
	return "";
}

string BiMap::key_from_value(string s) {
	for (auto i = 0; i < ordered_by_keys_.size(); i++) {
		if (s == ordered_by_keys_[i].second)
			return ordered_by_keys_[i].first;
	}
	return "";
}

bool BiMap::add(string key, string val) {
	auto key_itr = find_key(key);
	auto val_itr = find_value(val);
	pair<string, string> a = { key, val };
	bool v = true;
	bool k = true;
	for (auto i = 0; i < ordered_by_keys_.size(); i++) {
		if (key == ordered_by_keys_[i].first)
			k = false;
		if (val == ordered_by_keys_[i].second)
			v = false;
	}
	if ((v == true) && (k == true)) {
		ordered_by_keys_.insert(key_itr, a);
		ordered_by_vals_.insert(val_itr, a);
		return true;
	}

	else
		return false;
}

ostream & operator<<(ostream &out, BiMap &m)
{
	for (auto i = 0; i < m.ordered_by_keys_.size(); i++) {
		out << m.ordered_by_keys_[i].first << " : " << m.ordered_by_keys_[i].second;
		if (i < (m.ordered_by_keys_.size() - 1))
			out << ", ";
	}
	return out;
}