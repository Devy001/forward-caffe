// huangshize 2016.03.29
// === common.h ===

#ifndef JAFFE_COMMON_H_
#define JAFFE_COMMON_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

//using std::string;
//using std::vector;

//class Jaffe
//{
//public:
//	~Jaffe();
//
//	static Jaffe& Get();
//	inline static int solver_count() {return Get().solver_count_;}
//	inline static void set_solver_count(int val) { Get().solver_count_ = val; }
//	inline static bool root_solver() { return Get().root_solver_; }
//	inline static void set_root_solver(bool val) { Get().root_solver_ = val; }
//
//	int solver_count_;
//	bool root_solver_;
//private:
//	Jaffe();
//};

class JDatum {
public:
	JDatum() : m_channels(0), m_height(0), m_width(0), m_label(0), m_encoded(false) {}
	// Get
	inline int GetChannels() { return m_channels; }
	inline int GetHeight() { return m_height; }
	inline int GetWidth() { return m_width; }
	inline string GetData() { return m_data; }
	inline int GetLabel() { return m_label; }
	inline bool GetEncoded() { return m_encoded; }

	// Set
	inline void SetChannels(int channels) { m_channels = channels; }
	inline void SetHeight(int height) { m_height = height; }
	inline void SetWidth(int width) { m_width = width; }
	inline void SetData(string data) { m_data = data; }
	inline void SetLabel(int label) { m_label = label; }
	inline void SetEncoded(bool encoded) { m_encoded = encoded; }

private:
	int m_channels;
	int m_height;
	int m_width;

	string m_data;
	int m_label;
	bool m_encoded;
};

#endif