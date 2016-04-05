//Net ����ͷ�ļ�
#ifndef NET_PARAM_H_H
#define NET_PARAM_H_H

#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "jmatch.h"
#include "blob_shape.h"
#include "net_state.h"

using std::string; 
using std::cout;
using std::vector;
using std::ifstream;
using std::endl;

namespace jaffe {

	class JNetParameter{
	public:
		JNetParameter(){
			m_name = "";
			m_force_backward = false;
			m_debug_info = false;
			m_layer_num = 0;
		};
		~JNetParameter(){
			vector<string>(m_input).swap(m_input);
			vector<JBlobShape>(m_input_shape).swap(m_input_shape);
			vector<int>(m_input_dim).swap(m_input_dim);
			vector<vector<string>>(m_layers_param).swap(m_layers_param);

			delete m_state;
		};
		// ���ò����ļ�·��
		bool SetFilePath(const string filepath){
			m_filepath = filepath;
			return ReadParamFromText();
		};
		// ���ļ��ж�ȡ���� layer ����
		bool ReadParamFromText();

		int GetLayerNum(){ return m_layer_num; };
		// ����ָ������λ�õ�layer����
		vector<string> GetLayerParam(int idex){
			return m_layers_param[idex];
		}
	private:
		string m_filepath; // �ļ�·��

		string m_name; // ���� name
		vector<string> m_input;
		vector<JBlobShape> m_input_shape;
		vector<int> m_input_dim;
		bool m_force_backward;
		JNetState* m_state;
		bool m_debug_info;
		//vector<JLayerParam> m_layer;	//	��������LayerParameter�Ĵ��淽ʽ

		int m_layer_num; // �� net �� layer ������
		vector<vector<string>> m_layers_param;  // ���е� layer ����

		// ��ȡ����ʱʹ��������ʽƥ��
		//bool matchString(const string line, const string key, string* s);
	};
}

#endif