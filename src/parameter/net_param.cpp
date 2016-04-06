#include "net_param.h"

namespace jaffe {

	bool NPisleft(char c){
		return c == '{';
	}

	bool NPisright(char c){
		return c == '}';
	}

	bool JNetParameter::ReadParamFromText(){
		// ���ļ�
		ifstream fin;
		fin.open(m_filepath);
		if (!fin.is_open()){
			cout << "Failed to Open Net Parameter Prototxt" << endl;
			return false;
		}

		string line;
		bool b_enter_layer = false;
		bool b_enter_input_shape = false;
		bool b_enter_state = false;
		int i_left = 0;
		string str_temp = "";
		int i_temp = 0;
		vector<string> v_str_temp;
		// ���ж�ȡ����
		while (getline(fin, line)){
			line = DeleteSpace(line);
			// ��ֹͬһ layer �и����λ����ͬ����������
			bool b_enter_deep = b_enter_layer ||
				b_enter_input_shape || b_enter_state;
			if (!b_enter_deep){
				matchString(line, "name:", &m_name);

				if (matchString(line, "input:", &str_temp)){
					m_input.push_back(str_temp);
				}

				if (matchInt(line, "input_dim:", &i_temp)){
					m_input_dim.push_back(i_temp);
				}

				matchBool(line, "force_backward:",
					&m_force_backward);

				matchBool(line, "debug_info:", &m_debug_info);


			}
			// ���� BlobShape �����ռ�
			if (line.find("input_shape{") != string::npos){
				b_enter_input_shape = true;
				i_left += count_if(line.begin(), line.end(),
					NPisleft);
			}
			else if (b_enter_input_shape){
				v_str_temp.push_back(line);
				i_left += count_if(line.begin(), line.end(), NPisleft);
				i_left -= count_if(line.begin(), line.end(), NPisright);
				if (i_left == 0){
					v_str_temp.pop_back();//���һ����}����Ҫ����Ϊ��һ��"{"ûҪ
					JBlobShape temp_blob_shape;
					temp_blob_shape.SetParam(v_str_temp);
					m_input_shape.push_back(temp_blob_shape);//�� layer �������� layers_param ��
					v_str_temp.clear();
					b_enter_input_shape = false;
				}
			}
			// ���� LayerParameter �����ռ�
			if (line.find("layer{") != string::npos){
				b_enter_layer = true;
				m_layer_num++;
				i_left += count_if(line.begin(), line.end(),
					NPisleft);
			}
			else if (b_enter_layer){
				v_str_temp.push_back(line);
				i_left += count_if(line.begin(), line.end(), NPisleft);
				i_left -= count_if(line.begin(), line.end(), NPisright);
				if (i_left == 0){
					v_str_temp.pop_back();//���һ����}����Ҫ����Ϊ��һ��"{"ûҪ
					m_layers_param.push_back(v_str_temp);//�� layer �������� layers_param ��
					v_str_temp.clear();
					b_enter_layer = false;
				}
			}
			// ���� JNetState �����ռ�
			if (line.find("state{") != string::npos){
				b_enter_state = true;
				m_state = new JNetState;
				i_left += count_if(line.begin(), line.end(),
					NPisleft);
			}
			else if (b_enter_state){
				v_str_temp.push_back(line);
				i_left += count_if(line.begin(), line.end(),
					NPisleft);
				i_left -= count_if(line.begin(), line.end(),
					NPisright);
				if (i_left == 0){
					v_str_temp.pop_back();
					m_state->SetParam(v_str_temp);
					v_str_temp.clear();
					b_enter_state = false;
				}
			}
		}

		fin.close();
		return true;
	}

	string JNetParameter::DeleteSpace(const string line){
		string str_temp = line;
		bool b_enter = false;	//	˫�����ڿո񲻹�
		for (int i = 0; i < str_temp.length(); i++){
			if (str_temp.at(i) == ' ' && !b_enter){
				str_temp.erase(i,1);
			}
			else if (str_temp.at(i) == '"' && !b_enter){
				b_enter = true;
			}
			else if (b_enter && str_temp.at(i) == '"'){
				b_enter = false;
			}
		}
		return str_temp;
	}
} // namespace jaffe