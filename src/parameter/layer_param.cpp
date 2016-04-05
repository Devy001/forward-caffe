#include "layer_param.h"

namespace jaffe {

	bool LPisleft(char c){
		return c == '{';
	}

	bool LPisright(char c){
		return c == '}';
	}

	bool JLayerParam::SetType(const vector<string> param){
		string line;
		for (int i = 0; i < param.size(); i++){
			line = param.at(i);
			if(matchString(line, "type: ", &m_s_type)){
				return true;
			}
		}
		return false;
	}

	bool JLayerParam::SetSharedParam(const vector<string> param){
		string line;
		bool b_enter_param = false;
		bool b_enter_blobs = false;
		bool b_enter_include = false;
		bool b_enter_exclude = false;
		bool b_enter_transform_param = false;
		bool b_enter_loss_param = false;
		vector<string> v_str_temp;
		int left = 0;
		string str_temp = "";
		float f_temp = 0.0;
		bool b_temp = false;
		for (int i = 0; i < param.size(); i++){
			line = param.at(i);
			// ��ֹ�������ڳ���ͬ������
			bool b_enter_deep = b_enter_blobs || b_enter_exclude || 
				b_enter_include || b_enter_loss_param || 
				b_enter_param || b_enter_transform_param;
			if (!b_enter_deep){

				matchString(line, "name:", &m_s_name);
				matchString(line, "type:", &m_s_type);

				if (matchString(line, "bottom:", &str_temp)){
					m_s_bottom.push_back(str_temp);
				}

				if (matchString(line, "top:", &str_temp)){
					m_s_top.push_back(str_temp);
				}

				if (matchFloat(line, "loss_weight:", &f_temp)){
					m_s_loss_weight.push_back(f_temp);
				}

				if (matchBool(line, "propagate_down:", &b_temp)){
					m_s_propagate_down.push_back(b_temp);
				}
			}
			// ���� JParamSpec �����ռ�
			if (line.find(" param {") != string::npos){
				b_enter_param = true;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_param){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					JParamSpec param_temp;	// �����ж�� param_spec �����ռ�
					param_temp.SetParam(v_str_temp);
					m_s_param.push_back(param_temp);
					v_str_temp.clear();
					b_enter_param = false;
				}
			}
			// ���� JBlobProto �����ռ�
			if (line.find(" blobs {") != string::npos){
				b_enter_blobs = true;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_blobs){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					JBlobProto blobs_temp;	// �����ж�� blobs �����ռ�
					blobs_temp.SetParam(v_str_temp);
					m_s_blobs.push_back(blobs_temp);
					v_str_temp.clear();
					b_enter_blobs = false;
				}
			}
			// ���� JNetStateRule �����ռ䣨m_include��
			if (line.find("incude {") != string::npos){
				b_enter_include = true;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_include){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					JNetStateRule include_temp;	// �����ж�� include �����ռ�
					include_temp.SetParam(v_str_temp);
					m_s_include.push_back(include_temp);
					v_str_temp.clear();
					b_enter_include = false;
				}
			}
			// ���� JNetStateRule �����ռ䣨m_exclude��
			if (line.find("excude {") != string::npos){
				b_enter_exclude = true;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_exclude){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					JNetStateRule exclude_temp;	// �����ж�� exclude �����ռ�
					exclude_temp.SetParam(v_str_temp);
					m_s_exclude.push_back(exclude_temp);
					v_str_temp.clear();
					b_enter_exclude = false;
				}
			}
			// ���� JTransformationParam �����ռ�
			if (line.find("tranform_param {") != string::npos){
				b_enter_transform_param = true;
				m_s_transform_param = new JTransformationParam;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_transform_param){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					m_s_transform_param->SetParam(v_str_temp);
					v_str_temp.clear();
					b_enter_transform_param = false;
				}
			}
			// ���� JLossParam �����ռ�
			if (line.find("loss_param {") != string::npos){
				b_enter_loss_param = true;
				m_s_loss_param = new JLossParam;
				left += count_if(line.begin(), line.end(), LPisleft);
			}
			else if (b_enter_loss_param){
				v_str_temp.push_back(line);
				left += count_if(line.begin(), line.end(), LPisleft);
				left -= count_if(line.begin(), line.end(), LPisright);
				if (left == 0){
					v_str_temp.pop_back();
					m_s_loss_param->SetParam(v_str_temp);
					v_str_temp.clear();
					b_enter_loss_param = false;
				}
			}
		}

		return true;

	}

	bool JLayerParam::ShowSharedParam(){
		cout << "name: " << m_s_name << endl;
		cout << "type:" << m_s_type << endl;
		for (int i = 0; i < m_s_bottom.size(); i++){
			cout << "bottom[" << i << "]: " << m_s_bottom.at(i) 
				<< endl;
		}
		for (int i = 0; i < m_s_top.size(); i++){
			cout << "top[" << i << "]: " << m_s_top.at(i)
				<< endl;
		}
		for (int i = 0; i < m_s_loss_weight.size(); i++){
			cout << "loss_weight[" << i << "]: " << 
				m_s_loss_weight.at(i) << endl;
		}
		for (int i = 0; i < m_s_param.size(); i++){
			m_s_param.at(i).Show();
		}
		for (int i = 0; i < m_s_blobs.size(); i++){
			m_s_blobs.at(i).Show();
		}
		for (int i = 0; i < m_s_propagate_down.size(); i++){
			cout << "propagate_down[" << i << "]: " <<
				m_s_propagate_down.at(i) << endl;
		}
		for (int i = 0; i < m_s_include.size(); i++){
			m_s_include.at(i).Show();
		}
		for (int i = 0; i < m_s_exclude.size(); i++){
			m_s_exclude.at(i).Show();
		}
		if (m_s_transform_param)
			m_s_transform_param->Show();
		if (m_s_loss_param)
			m_s_loss_param->Show();
		return true;
	}
} // namespace jaffe
