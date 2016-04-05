#include "common_layers.h"

namespace jaffe {

	template class JSoftmaxLayer <int>;
	template class JSoftmaxLayer <float>;

	template <typename Dtype>
	bool JSoftmaxLayer<Dtype>::Init(const vector<string> param){
		SetParam(param);
		return ReadParam();
	}

	template <typename Dtype>
	bool JSoftmaxLayer<Dtype>::SetParam(const vector<string> param){
		return m_param->SetParam(param);
	}

	template <typename Dtype>
	bool JSoftmaxLayer<Dtype>::ReadParam(){
		return true;
	}

	template <typename Dtype>
	bool JSoftmaxLayer<Dtype>::Show(){
		return m_param->Show();
	}


} // namespace jaffe